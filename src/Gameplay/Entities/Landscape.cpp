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

#include "Gameplay/Entities/Landscape.hpp"

namespace nanowars {
namespace gameplay {
    namespace entities {

        bool LandscapeArea::operator==(const LandscapeArea& rhs)
        {
            return this->area.lowerBound == this->area.lowerBound && this->area.upperBound == rhs.area.upperBound && this->type == rhs.type;
        }

        Landscape::Landscape(GameWorld& parent, b2Body& body)
            : DestructableEntity(parent, body, EntityType::Landscape)
        {
        }

        void Landscape::addArea(LandscapeArea landscapeArea)
        {
            m_areas.push_back(landscapeArea);
        }

        void Landscape::removeArea(LandscapeArea landscapeArea)
        {
            m_areas.erase(std::remove(m_areas.begin(), m_areas.end(), landscapeArea), m_areas.end());
        }

        const vector<LandscapeArea>& Landscape::getAreas() const
        {
            return m_areas;
        }
    }
}
}
