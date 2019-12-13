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

#include "Gameplay/Jobs/RespawnJob.hpp"
#include "Gameplay/GameWorld.hpp"
#include "Gameplay/Entities/Rocket.hpp"

namespace nanowars {
namespace gameplay {
    namespace jobs {

        using namespace entities;

        RespawnJob::RespawnJob(GameWorld& gameWorld, EntityType entityType, EntityController* entityController, b2AABB respawnArea, float respawnInSeconds)
            : TimedJob(gameWorld, respawnInSeconds)
            , m_entityController(entityController)
            , m_entityType(entityType)
            , m_respawnArea(respawnArea)
        {
        }

        void RespawnJob::execute()
        {
            Rocket* rocket = m_gameWorld.spawn<Rocket>();
            rocket->getBody().SetTransform(m_respawnArea.GetCenter(), 0.0f);
            m_entityController->setEntity(rocket);
        }
    }
}
}