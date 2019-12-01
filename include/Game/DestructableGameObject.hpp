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

#include "Math/CollisionRing.hpp"
#include "Game/GameObject.hpp"
#include "Game/DestructableGameObjectDestroyer.hpp"

#include <SFML/Graphics/Image.hpp>
#include <vector>

namespace nanowars {
namespace game {

    using math::CollisionRing;
    using sf::Image;
    using std::vector;

    class DestructableGameObject : public GameObject
    {
    public:
        DestructableGameObject(GameWorld& parent, b2Body& body, GameObjectType gameObjectType);

        void initializeDestructableBehavior(const Image& textureSource);
        void destroy(const DestructableGameObjectDestroyer& destroyer);

    private:
        void destroyShape(const DestructableGameObjectDestroyer& destroyer);
        void destroyTexture(const DestructableGameObjectDestroyer& destroyer);

        struct FixtureCache
        {
            CollisionRing collisionRing;
            b2Fixture* fixture;
            FixtureCache(CollisionRing cr, b2Fixture* f)
                : collisionRing(cr)
                , fixture(f)
            {
            }
        };

        bool m_wasInitialized;
        Image m_textureSource;
        vector<FixtureCache> m_fixtureCache;
    };
}
}