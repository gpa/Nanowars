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

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Math/CollisionRing.hpp"

namespace nanowars {
namespace util {

    using namespace math;

    class Box2DConverter
    {
    public:
        static CollisionRing circleToCollisionRing(b2Vec2 position, float radius, unsigned vertexCount);
        static sf::Color toSfmlColor(const b2Color& color, sf::Uint8 alpha = 255);
        static sf::Vector2f toSfmlVector(const b2Vec2& vector, bool scaleToPixels = true);
    };
}
}