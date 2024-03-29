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

#include "Gameplay/Jobs/Job.hpp"
#include <SFML/System/Clock.hpp>

namespace nanowars {
namespace gameplay {
    namespace jobs {

        using sf::Clock;

        class TimedJob : public Job
        {
        public:
            TimedJob(GameWorld& gameWorld, float executionTimeout)
                : Job(gameWorld)
                , m_executionTimeout(executionTimeout)
            {
            }

            inline bool shouldExecute() override
            {
                return m_timer.getElapsedTime().asSeconds() >= m_executionTimeout;
            }

        private:
            Clock m_timer;
            float m_executionTimeout;
        };
    }
}
}