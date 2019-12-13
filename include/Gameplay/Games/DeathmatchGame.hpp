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

#include "Gameplay/Entities/Landscape.hpp"
#include "Gameplay/Games/Game.hpp"
#include "Gameplay/Controllers/EntityController.hpp"
#include <SFML/System/Clock.hpp>

namespace nanowars {
namespace gameplay {
    namespace games {

        using controllers::EntityController;
        using namespace entities;
        using sf::Clock;

        class DeathmatchGame : public Game
        {
        public:
            DeathmatchGame(AssetHolder& assetHolder, GameInfo gameInfo, vector<shared_ptr<EntityController>> controllers);
            void initialize() override;
            void update(float dt) override;

        private: 
            void onEntitySpawned(GameWorld& gameWorld, Entity& entity);
            void onEntityKilled(GameWorld& gameWorld, Entity& entity);

            struct ControllerWithInfo
            {
                shared_ptr<EntityController> controller;
                LandscapeArea launchpad;
            };

            Clock m_gameClock;
            vector<ControllerWithInfo> m_controllerInfos;
        };
    }
}
}