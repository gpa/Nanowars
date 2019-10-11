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

#include "Game/Factories/BulletFactory.hpp"
#include "Game/GameObjects/Bullet.hpp"
#include "Core/Constants.hpp"

namespace nanowars {
namespace game {
    namespace factories {

        void BulletFactory::build(GameWorld& gameWorld, AssetHolder& assetHolder, GameObject& gameObject)
        {
            Bullet* bullet = static_cast<Bullet*>(&gameObject);
            b2Body& body = bullet->getBody();

            float radius = 100.0f / core::constants::meterToPixelRatio;
            b2FixtureDef def;
            body.SetGravityScale(0.0f);
            def.density = 0.3f;
            def.friction = 0.f;
            b2CircleShape c;
            c.m_radius = radius;
            def.shape = &c;
            body.CreateFixture(&def);
        }
    }
}
}
