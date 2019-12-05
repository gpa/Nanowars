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

#include "Game/GameWorld.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace nanowars {
namespace game {

    GameWorld::GameWorld(AssetHolder& assetHolder)
        : m_world(b2Vec2(0.0f, 9.8f))
        , m_assetHolder(assetHolder)
    {
        m_world.SetContactFilter(&m_contactManager);
        m_world.SetContactListener(&m_contactManager);
    }

    void GameWorld::step(float dt)
    {
        beforeStep();
        m_world.Step(dt, 6, 2);
        for (auto& o : m_objects)
            o->update(dt);
        afterStep();
    }

    void GameWorld::beforeStep()
    {
    }

    void GameWorld::afterStep()
    {
        m_contactManager.ProcessContacts();

        for (GameObject* s : m_objectsToRemoveCache)
        {
            int index = -1;
            for (int i = 0; i < m_objects.size(); ++i)
            {
                if (m_objects[i].get() == s)
                {
                    index = i;
                    break;
                }
            }
            if (index != -1)
            {
                m_world.DestroyBody(&s->getBody());
                m_objects.erase(m_objects.begin() + index);
            }
        }
        m_objectsToRemoveCache.clear();
    }

    void GameWorld::reset()
    {
        for (auto& body : m_objects)
            m_world.DestroyBody(&body->getBody());

        m_objects.clear();
        m_objectsToRemoveCache.clear();
    }
}
}
