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

#include "Gameplay/GameWorldContactManager.hpp"
#include "Gameplay/Entities/Bullet.hpp"

namespace nanowars {
namespace gameplay {

    using namespace entities;

    bool GameWorldContactManager::ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB)
    {
        auto* a = static_cast<Entity*>(fixtureA->GetBody()->GetUserData());
        auto* b = static_cast<Entity*>(fixtureB->GetBody()->GetUserData());
        if (a->getType() == EntityType::Bullet && b->getType() == EntityType::Bullet)
            return false;

        if (a->getType() == EntityType::Bullet && b->getType() == EntityType::Rocket)
        {
            if (reinterpret_cast<Bullet*>(a)->getFiredBy() == reinterpret_cast<Rocket*>(b))
                return false;
        }

        if (a->getType() == EntityType::Rocket && b->getType() == EntityType::Bullet)
        {
            if (reinterpret_cast<Bullet*>(b)->getFiredBy() == reinterpret_cast<Rocket*>(a))
                return false;
        }

        if (a->getType() == EntityType::Bullet && b->getType() == EntityType::Bullet)
            return false;

        return true;
    }

    bool GameWorldContactManager::ShouldCollide(b2Fixture* fixture, b2ParticleSystem* particleSystem, int32 particleIndex)
    {
        auto type = static_cast<Entity*>(fixture->GetBody()->GetUserData())->getType();

        if (static_cast<Entity*>(fixture->GetBody()->GetUserData())->getType() == EntityType::Landscape)
            return true;

        return false;
    }

    bool GameWorldContactManager::ShouldCollide(b2ParticleSystem* particleSystem, int32 particleIndexA, int32 particleIndexB)
    {
        return false;
    }

    void GameWorldContactManager::BeginContact(b2Contact* c)
    {
        auto* a = static_cast<Entity*>(c->GetFixtureA()->GetBody()->GetUserData());
        auto* b = static_cast<Entity*>(c->GetFixtureB()->GetBody()->GetUserData());

        m_collisionCache.push_back(std::make_pair(a, b));
    }

    void GameWorldContactManager::ProcessContacts()
    {
        for (const auto& collision : m_collisionCache)
        {
            collision.first->onCollision(*collision.second);
            collision.second->onCollision(*collision.first);
        }

        m_collisionCache.clear();
    }
}
}