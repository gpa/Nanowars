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

#include "Math/Vector2.hpp"
#include <Box2D/Box2D.h>
#include <vector>

namespace nanowars {
namespace algorithms {

    using math::Vector2f;
    using std::vector;

    class LaunchPadFinder
    {
    public:
        // Finds the best place to spawn rockets on a randomly generated map
        static vector<Vector2f> getBestLaunchPodPositions(b2Body& landscape);
    };
}
}