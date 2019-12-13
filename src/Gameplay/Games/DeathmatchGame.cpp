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
#include "Gameplay/Controllers/RocketController.hpp"
#include "Gameplay/Jobs/RespawnJob.hpp"

namespace nanowars {
namespace gameplay {
    namespace games {

        using namespace entities;
        using namespace controllers;

        DeathmatchGame::DeathmatchGame(AssetHolder& assetHolder, GameInfo gameInfo, vector<shared_ptr<EntityController>> controllers)
            : Game(assetHolder, gameInfo)
        {
            for (auto& controller : controllers)
            {
                ControllerWithInfo controllerWithInfo;
                controllerWithInfo.controller = controller;
                m_controllerInfos.push_back(controllerWithInfo);
            }
        }

        void DeathmatchGame::update(float dt)
        {
            if (m_gameClock.getElapsedTime().asSeconds() > m_gameInfo.deathmatchGameInfo.gameTimeout)
                m_gameInfo.state = GameState::Finished;

            for (auto& controllerInfo : m_controllerInfos)
            {
                if (controllerInfo.controller->getPlayer().getKills() >= m_gameInfo.deathmatchGameInfo.killsTimeout)
                    m_gameInfo.state = GameState::Finished;
            }

            Game::update(dt);
        }

        void DeathmatchGame::initialize()
        {
            m_gameWorld = std::make_shared<GameWorld>(m_assetHolder);
            m_gameWorld->registerFactory(EntityType::Landscape, std::make_shared<LandscapeFactory>());
            m_gameWorld->registerFactory(EntityType::Rocket, std::make_shared<RocketFactory>());
            m_gameWorld->registerFactory(EntityType::Bullet, std::make_shared<BulletFactory>());

            auto* landscape = m_gameWorld->spawn<Landscape>();
            auto& areas = landscape->getAreas();
            for (int i = 0; i < areas.size(); ++i)
            {
                m_controllerInfos[i].launchpad = areas[i];
                RespawnJob respawnJob(*(m_gameWorld.get()), EntityType::Rocket, m_controllerInfos[i].controller.get(), areas[i].area, 0.0f);
                respawnJob.execute();
            }

            m_gameWorld->addEntitySpawnedSlot(std::bind(&DeathmatchGame::onEntitySpawned, this, std::placeholders::_1, std::placeholders::_2));
            m_gameWorld->addEntityKilledSlot(std::bind(&DeathmatchGame::onEntityKilled, this, std::placeholders::_1, std::placeholders::_2));
            m_gameClock.restart();
        }

        void DeathmatchGame::onEntitySpawned(GameWorld& gameWorld, Entity& entity)
        {
        }

        void DeathmatchGame::onEntityKilled(GameWorld& gameWorld, Entity& entity)
        {
            if (entity.getType() == EntityType::Rocket)
            {
                for (auto& controllerInfo : m_controllerInfos)
                {
                    if (controllerInfo.controller->getEntity() == &entity)
                    {
                        controllerInfo.controller->resetEntity();
                        auto& gameWorld = *m_gameWorld.get();
                        auto* controller = controllerInfo.controller.get();
                        auto entityType = entity.getType();
                        auto respawnArea = controllerInfo.launchpad.area;
                        auto respawnTimeout = m_gameInfo.deathmatchGameInfo.respawnTimeout;

                        auto respawnJob = std::make_shared<RespawnJob>(gameWorld, entityType, controller, respawnArea, respawnTimeout);
                        m_jobs.push_back(respawnJob);
                    }
                }
            }
        }
    }
}
}