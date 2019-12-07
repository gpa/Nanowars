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

#include "Gameplay/Entities/Rocket.hpp"
#include "Gameplay/Entities/Bullet.hpp"
#include "Gameplay/GameWorld.hpp"

namespace nanowars {
namespace gameplay {
    namespace entities {

        Rocket::Rocket(GameWorld& parent, b2Body& body)
            : Entity(parent, body, EntityType::Rocket)
            , m_thrustParticleSystem(body)
        {
        }

        void Rocket::setEquipment(vector<RocketEngine> engines, vector<RocketWeaponSlot> weaponSlots)
        {
            m_engines = engines;
            m_weaponSlots = weaponSlots;
        }

        void Rocket::applyMainThrust()
        {
            applyThrustFromEngines(RocketEngine::EngineType::Main);
        }

        void Rocket::applyLeftThrust()
        {
            applyThrustFromEngines(RocketEngine::EngineType::PositionalLeft);
        }

        void Rocket::applyRightThrust()
        {
            applyThrustFromEngines(RocketEngine::EngineType::PositionalRight);
        }

        void Rocket::shoot()
        {
            for (auto& w : m_weaponSlots)
            {
                auto v = m_body.GetWorldVector(w.direction);
                auto p = m_body.GetWorldPoint(w.position);
                m_parent.spawn<Bullet>(this, p, v);
            }
        }

        void Rocket::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            Entity::draw(target, states);
        }

        void Rocket::applyThrustFromEngines(RocketEngine::EngineType type)
        {
            for (const RocketEngine& e : m_engines)
            {
                if (e.type == type)
                {
                    auto f = m_body.GetWorldVector(e.force);
                    auto p = m_body.GetWorldPoint(e.position);

                    m_body.ApplyForce(f, p, true);
                    m_thrustParticleSystem.fire(p, -f);
                }
            }
        }
    }
}
}
