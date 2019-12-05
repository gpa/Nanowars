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

#include "Algorithms/ImagePainter.hpp"

namespace nanowars {
namespace algorithms {

    using namespace std;

    void ImagePainter::drawLine(int x0, int y0, int x1, int y1, sf::Image& img, const sf::Color& color)
    {
        int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
        int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
        int err = (dx > dy ? dx : -dy) / 2, e2;

        for (;;)
        {
            img.setPixel(x0, y0, color);
            if (x0 == x1 && y0 == y1)
                break;
            e2 = err;
            if (e2 > -dx)
            {
                err -= dy;
                x0 += sx;
            }
            if (e2 < dy)
            {
                err += dx;
                y0 += sy;
            }
        }
    }

    void ImagePainter::scanLineFill(Image& bmp, const Color& boundaryColor, const Color& replacementColor)
    {
        auto targetColor = boundaryColor;
        for (unsigned y = 0; y < bmp.getSize().y; ++y)
        {
            unsigned x = 0;
            while (x < bmp.getSize().x && bmp.getPixel(x, y) != targetColor)
            {
                x++;
            }
            while (x < bmp.getSize().x && bmp.getPixel(x, y) == targetColor)
            {
                bmp.setPixel(x, y, replacementColor);
                x++;
            }
            bool hasFinish = false;
            for (unsigned k = x; k < bmp.getSize().x; ++k)
            {
                if (bmp.getPixel(k, y) == targetColor)
                {
                    bmp.setPixel(x, y, replacementColor);
                    hasFinish = true;
                    break;
                }
            }
            if (hasFinish)
            {
                while (x < bmp.getSize().x && bmp.getPixel(x, y) != targetColor)
                {
                    bmp.setPixel(x, y, replacementColor);
                    x++;
                }
                while (x < bmp.getSize().x && bmp.getPixel(x, y) == targetColor)
                {
                    bmp.setPixel(x, y, replacementColor);
                    x++;
                }
            }
        }
    }

    Vector2u ImagePainter::drawShape(CollisionRing collisionRing, float shapeScaleX, float shapeScaleY, float vertexScale, Image& original, Image& bmp, const Color& boundaryColor)
    {
        float sx = shapeScaleX;
        float sy = shapeScaleY;
        float w = static_cast<float>(original.getSize().x);
        float h = static_cast<float>(original.getSize().y);

        vector<std::pair<b2Vec2, b2Vec2>> segments;

        float maxX = FLT_MIN;
        float maxY = FLT_MIN;
        float minX = FLT_MAX;
        float minY = FLT_MAX;

        boost::geometry::model::ring<b2Vec2, false, true>
            shape(collisionRing.getVertices(), collisionRing.getVertices() + collisionRing.getCount());

        // get the segments from the subtraction ring
        // and transform the vertices to map pixels, also take the map image scale &
        // origin into account.
        boost::geometry::for_each_segment(
            shape, [&](boost::geometry::model::referring_segment<b2Vec2> s) {
                float x0 = (((s.first.x * vertexScale))) / sx;
                float x1 = (((s.second.x * vertexScale))) / sx;
                float y0 = ((((s.first.y * vertexScale))) / sy);
                float y1 = ((((s.second.y * vertexScale))) / sy);

                y0 = y0 > h ? h : y0 < 0 ? 0 : y0;
                y1 = y1 > h ? h : y1 < 0 ? 0 : y1;
                y0 = y0 == h ? y0 - 1 : y0;
                y1 = y1 == h ? y1 - 1 : y1;

                x0 = x0 > w ? w : x0 < 0 ? 0 : x0;
                x1 = x1 > w ? w : x1 < 0 ? 0 : x1;
                x0 = x0 == w ? x0 - 1 : x0;
                x1 = x1 == w ? x1 - 1 : x1;

                maxX = max(max(maxX, x0), x1);
                maxY = max(max(maxY, y0), y1);
                minX = min(min(minX, x0), x1);
                minY = min(min(minY, y0), y1);

                segments.push_back(std::make_pair(b2Vec2(x0, y0), b2Vec2(x1, y1)));
            });

        maxX = maxY = 0;
        for (auto& seg : segments)
        {
            seg.first.x -= minX;
            seg.second.x -= minX;
            seg.first.y -= minY;
            seg.second.y -= minY;
            maxX = max(max(maxX, seg.first.x), seg.second.x);
            maxY = max(max(maxY, seg.first.y), seg.second.y);
        }

        // Now we got the subtraction shape vertices in [0, w][0, h] range
        // also they're nicely scaled for our map.

        // Generate a new image as big as the subtraction shape
        bmp.create(static_cast<unsigned>(maxX + 1), static_cast<unsigned>(maxY + 1));

        // fill the image with the pixels from the original map
        // so basically the small subtraction shape becomes a copy of a part of the
        // original image
        for (unsigned y = 0; y < bmp.getSize().y; ++y)
        {
            for (unsigned x = 0; x < bmp.getSize().x; ++x)
            {
                bmp.setPixel(x, y, original.getPixel(static_cast<int>(minX) + x, static_cast<int>(minY) + y));
            }
        }

        // draw the outline lines from the shape to the image
        for (auto seg : segments)
        {
            int x0 = static_cast<int>(seg.first.x);
            int y0 = static_cast<int>(seg.first.y);
            int x1 = static_cast<int>(seg.second.x);
            int y1 = static_cast<int>(seg.second.y);

            ImagePainter::drawLine(
                x0, y0, x1, y1, bmp, boundaryColor);
        }

        return Vector2u(static_cast<unsigned>(minX), static_cast<unsigned>(minY));
    }
}
}