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

#include "Gameplay/Games/DeathmatchGame.hpp"
#include "Gameplay/Factories/RocketFactory.hpp"
#include "Gameplay/Factories/LandscapeFactory.hpp"
#include "Gameplay/Factories/BulletFactory.hpp"

namespace nanowars {
namespace gameplay {
    namespace games {

        using namespace entities;

        DeathmatchGame::DeathmatchGame(GameManager& gameManager, GameWorld& gameWorld, AssetHolder& assetHolder, GameInfo gameInfo)
            : Game(gameManager, gameWorld, assetHolder, gameInfo)
        {
        }

        void DeathmatchGame::initialize()
        {
            m_gameWorld.registerFactory<Landscape>(std::make_shared<LandscapeFactory>());
            m_gameWorld.registerFactory<Rocket>(std::make_shared<RocketFactory>());
            m_gameWorld.registerFactory<Bullet>(std::make_shared<BulletFactory>());

            Landscape* landscape = m_gameWorld.spawn<Landscape>();
            for (auto& area : landscape->getAreas())
            {
                Rocket* rocket = m_gameWorld.spawn<Rocket>();
                rocket->getBody().SetTransform(area.area.GetCenter(), 0.0f);
            }
        }
    }
}
}