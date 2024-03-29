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

#include "Gameplay/Entity.hpp"
#include "Gameplay/GameWorldContactManager.hpp"
#include "Gameplay/Factories/EntityFactory.hpp"
#include "Asset/AssetHolder.hpp"

#include "Math/AABB.hpp"

#include <Box2D/Box2D.h>

#include <memory>
#include <vector>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <functional>
#include <boost/signals2.hpp>

namespace nanowars {
namespace debug {
    class DebugManager;
}
namespace gameplay {

    using std::unique_ptr;
    using std::shared_ptr;
    using std::vector;
    using std::unordered_map;
    using std::function;
    using math::AABB;
    using namespace boost;
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

        const vector<unique_ptr<Entity>>& getEntities() const;
        const vector<unique_ptr<Entity>>& getEntities(AABB region) const;

        template <typename T, class... Args>
        T* spawn(Args... args);
        void kill(Entity& Entity);

        void registerFactory(EntityType entityType, shared_ptr<EntityFactory> factory);
        void deregisterFactory(EntityType entityType);

        typedef signals2::signal<void(GameWorld&, Entity&)>  entityLifetimeSignal_t;
        signals2::connection addEntitySpawnedSlot(entityLifetimeSignal_t::slot_type slot);
        signals2::connection addEntityKilledSlot(entityLifetimeSignal_t::slot_type slot);

    private:
        void beforeStep();
        void afterStep();

        b2World m_world;
        AssetHolder& m_assetHolder;
        GameWorldContactManager m_contactManager;

        vector<unique_ptr<Entity>> m_entities;
        unordered_map<EntityType, shared_ptr<EntityFactory>> m_factories;

        entityLifetimeSignal_t m_entitySpawnedSignal;
        entityLifetimeSignal_t m_entityKilledSignal;

        vector<Entity*> m_entitiesToRemoveCache;
        friend class debug::DebugManager;
    };

    template <typename T, class... Args>
    inline T* GameWorld::spawn(Args... args)
    {
        static_assert(std::is_base_of<Entity, T>::value);
        auto bodyDef = b2BodyDef();
        b2Body* body = m_world.CreateBody(&bodyDef);
        T* entity = new T(*this, *body, args...);
        m_entities.push_back(std::move(unique_ptr<T>(entity)));
        m_factories[entity->getType()]->build(*this, m_assetHolder, *entity);
        m_entitySpawnedSignal(*this, *entity);
        return entity;
    }

    inline void GameWorld::kill(Entity& entity)
    {
        m_entitiesToRemoveCache.push_back(&entity);
        m_entityKilledSignal(*this, entity);
    }

    inline void GameWorld::registerFactory(EntityType entityType, shared_ptr<EntityFactory> factory)
    {
        m_factories[entityType] = factory;
    }

    inline void GameWorld::deregisterFactory(EntityType entityType)
    {
        m_factories.erase(entityType);
    }

    inline const vector<unique_ptr<Entity>>& GameWorld::getEntities() const
    {
        return m_entities;
    }

    inline const vector<unique_ptr<Entity>>& GameWorld::getEntities(AABB region) const
    {
        return m_entities;
    }
}
}