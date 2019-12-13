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

#include "Gameplay/Games/Game.hpp"
#include "Gameplay/GameManager.hpp"

namespace nanowars {
namespace gameplay {
    namespace games {

        Game::Game(AssetHolder& assetHolder, GameInfo gameInfo)
            : m_gameInfo(gameInfo)
            , m_assetHolder(assetHolder)
        {
            m_gameInfo.state = GameState::InProgress;
        }

        void Game::update(float dt)
        {
            if (m_gameWorld)
                m_gameWorld->step(dt);

            for (int i = 0; i < m_jobs.size(); ++i)
            {
                if (m_jobs[i]->shouldExecute())
                {
                    m_jobs[i]->execute();
                    m_jobs.erase(m_jobs.begin() + i);
                    i--;
                }
            }
        }

        const GameInfo& Game::getGameInfo() const
        {
            return m_gameInfo;
        }

        const GameWorld& Game::getGameWorld() const
        {
            return *m_gameWorld.get();
        }
    }
}
}