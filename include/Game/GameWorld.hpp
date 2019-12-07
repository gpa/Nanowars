/*
Copyright (c) 2019 Gratian Pawliszyn
This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option)
any later version.
This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
more details.
You should have received a copy of the GNU General Public License along with
this program. If not, see <http://www.gnu.org/licenses/>. */

#pragma once

#include "Game/GameObject.hpp"
#include "Game/GameWorldContactManager.hpp"
#include "Game/Factories/GameObjectFactory.hpp"
#include "Asset/AssetHolder.hpp"

#include "Math/AABB.hpp"

#include <Box2D/Box2D.h>

#include <memory>
#include <vector>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

namespace nanowars {
namespace debug {
    class DebugManager;
}
namespace game {

    using std::unique_ptr;
    using std::shared_ptr;
    using std::vector;
    using std::unordered_map;
    using math::AABB;

    using namespace factories;
    using namespace asset;

    class GameWorld
    {
    public:
        GameWorld(AssetHolder& assetHolder);
        ~GameWorld();

		GameWorld(const GameWorld& other) = delete;
        GameWorld& operator=(const GameWorld& other) = delete;

        void step(float dt);

        const vector<unique_ptr<GameObject>>& getGameObjects() const;
        const vector<unique_ptr<GameObject>>& getGameObjects(AABB region) const;

        template <typename T, class... Args>
        T* spawn(Args... args);
        void kill(GameObject& gameObject);

        template <typename TGameObjectType>
        void registerFactory(shared_ptr<GameObjectFactory> factory);
        template <typename TGameObjectType>
        void deregisterFactory();

    private:
        void beforeStep();
        void afterStep();

        b2World m_world;
        AssetHolder& m_assetHolder;
        GameWorldContactManager m_contactManager;

        vector<unique_ptr<GameObject>> m_objects;
        unordered_map<std::type_index, shared_ptr<GameObjectFactory>> m_factories;

        vector<GameObject*> m_objectsToRemoveCache;
        friend class debug::DebugManager;
    };

    template <typename T, class... Args>
    inline T* GameWorld::spawn(Args... args)
    {
        static_assert(std::is_base_of<GameObject, T>::value);
        auto bodyDef = b2BodyDef();
        b2Body* body = m_world.CreateBody(&bodyDef);
        T* gameObject = new T(*this, *body, args...);
        m_objects.push_back(std::move(unique_ptr<T>(gameObject)));
        m_factories[typeid(T)]->build(*this, m_assetHolder, *gameObject);
        return gameObject;
    }

    inline void GameWorld::kill(GameObject& gameObject)
    {
        m_objectsToRemoveCache.push_back(&gameObject);
    }

    template <typename TGameObjectType>
    void GameWorld::registerFactory(shared_ptr<GameObjectFactory> factory)
    {
        static_assert(std::is_base_of<GameObject, TGameObjectType>::value);
        m_factories[typeid(TGameObjectType)] = factory;
    }

    template <typename TGameObjectType>
    void GameWorld::deregisterFactory()
    {
        static_assert(std::is_base_of<GameObject, TGameObjectType>::value);
        m_factories.erase(typeid(TGameObjectType));
    }

    inline const vector<unique_ptr<GameObject>>& GameWorld::getGameObjects() const
    {
        return m_objects;
    }

    inline const vector<unique_ptr<GameObject>>& GameWorld::getGameObjects(AABB region) const
    {
        return m_objects;
    }
}
}