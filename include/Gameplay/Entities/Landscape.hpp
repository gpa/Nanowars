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

#include "Gameplay/DestructableEntity.hpp"
#include <vector>

namespace nanowars {
namespace gameplay {
    namespace entities {

        struct LandscapeArea
        {
            enum class LandscapeAreaType
            {
                Launchpad
            };

            b2AABB area;
            LandscapeAreaType type;

            bool operator==(const LandscapeArea& rhs);
        };

        class Landscape : public DestructableEntity
        {
        public:
            Landscape(GameWorld& parent, b2Body& body);

            void addArea(LandscapeArea landscapeArea);
            void removeArea(LandscapeArea landscapeArea);

            const vector<LandscapeArea>& getAreas() const;

        private:
            vector<LandscapeArea> m_areas;
        };
    }
}
}