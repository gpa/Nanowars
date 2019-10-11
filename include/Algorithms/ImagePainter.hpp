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

#include "Math/CollisionRing.hpp"
#include <SFML/Graphics/Image.hpp>

namespace nanowars {
namespace algorithms {

    using sf::Image;
    using sf::Color;
    using math::CollisionRing;

    class ImagePainter
    {
    public:
        static void drawLine(int x0, int y0, int x1, int y1, Image& img, const Color& color);
        static b2Vec2 drawShape(CollisionRing shape, float shapeScaleX, float shapeScaleY, float vertexScale, Image& original, Image& bmp, const Color& boundaryColor);
        static void scanLineFill(Image& img, const Color& boundaryColor, const Color& replacementColor);
    };
}
}