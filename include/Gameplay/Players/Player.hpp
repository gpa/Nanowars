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
        
        using std::string;

        class Player
        {
        public:
            Player(string name)
                : m_name(name)
                , m_team(nullptr)
                , m_kills(0)
                , m_deaths(0)
                , m_capturedFlags(0)
            {
            }

            inline string getName() { return m_name; }
            inline Team* getTeam() { return m_team; }
            inline int getKills() { return m_kills; }
            inline int getDeaths() { return m_deaths; }
            inline int getCapturedFlags() { return m_capturedFlags; }
            
            inline void addKill() { m_kills++; }
            inline void addDeath() { m_deaths++; }
            inline void addCapturedFlag() { m_capturedFlags++; }

        private:
            string m_name;
            Team* m_team;
            int m_kills;
            int m_deaths;
            int m_capturedFlags;
        };
    }
}
}