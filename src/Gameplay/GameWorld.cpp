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

#include "Gameplay/GameWorld.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace nanowars {
namespace gameplay {

    GameWorld::GameWorld(AssetHolder& assetHolder)
        : m_world(b2Vec2(0.0f, 9.8f))
        , m_assetHolder(assetHolder)
    {
        m_world.SetContactFilter(&m_contactManager);
        m_world.SetContactListener(&m_contactManager);
    }

    GameWorld::~GameWorld()
    {
        // our entities have to be deallocated before b2World
        m_entities.clear();
        m_entitiesToRemoveCache.clear();
    }

    void GameWorld::step(float dt)
    {
        beforeStep();
        m_world.Step(dt, 6, 2);
        for (auto& o : m_entities)
            o->update(dt);
        afterStep();
    }

    void GameWorld::beforeStep()
    {
    }

    signals2::connection GameWorld::addEntitySpawnedSlot(entityLifetimeSignal_t::slot_type slot)
    {
        return m_entitySpawnedSignal.connect(slot);
    }

    signals2::connection GameWorld::addEntityKilledSlot(entityLifetimeSignal_t::slot_type slot)
    {
        return m_entityKilledSignal.connect(slot);
    }

    void GameWorld::afterStep()
    {
        m_contactManager.ProcessContacts();

        for (Entity* s : m_entitiesToRemoveCache)
        {
            int index = -1;
            for (int i = 0; i < m_entities.size(); ++i)
            {
                if (m_entities[i].get() == s)
                {
                    index = i;
                    break;
                }
            }
            if (index != -1)
            {
                b2Body* body = &s->getBody();
                m_entities.erase(m_entities.begin() + index);
                m_world.DestroyBody(body);
            }
        }
        m_entitiesToRemoveCache.clear();
    }
}
}
