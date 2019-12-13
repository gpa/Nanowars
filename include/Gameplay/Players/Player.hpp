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

#include "Gameplay/Players/Team.hpp"
#include <string>

namespace nanowars {
namespace gameplay {
    namespace players {
        class Player
        {
        public:
            Player(std::string name)
                : m_name(name)
                , m_team(nullptr)
                , m_kills(0)
                , m_deaths(0)
                , m_capturedFlags(0)
            {
            }

        private:
            std::string m_name;
            Team* m_team;
            int m_kills;
            int m_deaths;
            int m_capturedFlags;
        };
    }
}
}