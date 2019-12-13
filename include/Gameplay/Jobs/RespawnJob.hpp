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

#include "Gameplay/Jobs/TimedJob.hpp"
#include "Gameplay/Controllers/EntityController.hpp"
#include <typeinfo>

namespace nanowars {
namespace gameplay {
    namespace jobs {

        using controllers::EntityController;

        class RespawnJob : public TimedJob
        {
        public:
            RespawnJob(GameWorld& gameWorld, EntityType entityType, EntityController* controller, b2AABB respawnArea, float respawnInSeconds);

            void execute() override;

        private:
            EntityController* m_entityController;
            b2AABB m_respawnArea;
            EntityType m_entityType;
        };
    }
}
}