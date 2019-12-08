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

#include "Gameplay/Entities/Bullet.hpp"
#include "Gameplay/Entities/Rocket.hpp"
#include "Gameplay/Entities/Landscape.hpp"
#include "Gameplay/GameWorld.hpp"
#include "Core/Constants.hpp"
#include "Util/Box2DConverter.hpp"

#include <SFML/Graphics.hpp>

namespace nanowars {
namespace gameplay {
    namespace entities {

        Bullet::Bullet(GameWorld& parent, b2Body& body, Rocket* firedBy, b2Vec2 position, b2Vec2 velocity)
            : SelfDestructableEntity(parent, body, EntityType::Bullet, 2.0f)
            , m_firedBy(firedBy)
        {
            body.SetTransform(position, 0.0f);
            body.SetLinearVelocity(velocity);
        }

        void Bullet::onCollision(Entity& other)
        {
            if (other.getType() == EntityType::Landscape)
            {
                Landscape* landscape = static_cast<Landscape*>(&other);
                landscape->destroy(*this);
            }

            m_parent.kill(*this);
        }

        Rocket* Bullet::getFiredBy()
        {
            return m_firedBy;
        }

        CollisionRing Bullet::getCollisionRing() const
        {
            b2CircleShape* circleShape = static_cast<b2CircleShape*>(m_body.GetFixtureList()->GetShape());
            float radius = circleShape->m_radius * 2.0f;
            b2Vec2 position = m_body.GetPosition();

            return util::Box2DConverter::circleToCollisionRing(position, radius, 30);
        }

        void Bullet::draw(sf::RenderTarget& target, sf::RenderStates) const
        {
        }
    }
}
}