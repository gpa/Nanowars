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

#include "Math/Vector2.hpp"
#include "Math/CollisionRing.hpp"
#include "Util/ImageAccessor.hpp"

#include <vector>

namespace nanowars {
namespace algorithms {

    using namespace math;
    using namespace util;

    using std::vector;

    class ImageToMapGenerator
    {
    public:
        ImageToMapGenerator(Vector2f divisionFactor, float simplificationFactor);

        vector<CollisionRing> getCollisionRings(const ImageAccessor& imageAccessor) const;

    private:
        float m_simplificationFactor;
        Vector2f m_divisionFactor;
    };
}
}