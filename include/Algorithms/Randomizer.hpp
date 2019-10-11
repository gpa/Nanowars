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

#include <cstdlib>
#include <ctime>

namespace nanowars {
namespace algorithms {

    class Randomizer
    {
    public:
        static void setSeed(unsigned int seed);
        static unsigned int getSeed();

        static float random(float begin, float end);
        static int random(int begin, int end);

    private:
        static unsigned int m_seed;

        static unsigned int initSeed();
    };
}
}