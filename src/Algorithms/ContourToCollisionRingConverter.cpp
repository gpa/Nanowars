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

#include "Algorithms/ContourToCollisionRingConverter.hpp"
#include "Math/Vector2.hpp"

namespace nanowars {
namespace algorithms {

    using namespace math;

    struct Pixel
    {
        Vector2i corners[4];
        Pixel(int x, int y)
        {
            corners[0] = { x, y };
            corners[1] = { x + 1, y };
            corners[2] = { x + 1, y + 1 };
            corners[3] = { x, y + 1 };
        }

        int getNextCornerIndex(Vector2i position)
        {
            for (unsigned i = 0; i < 4; ++i)
                if (corners[i] == position)
                    return i;
            return -1;
        }
    };

    CollisionRing ContourToCollisionRingConverter::convert(ContourTracer::contour_t contour)
    {
        std::vector<Vector2i> vertices;
        for (unsigned i = 0, cornerId = 0; i < contour.size() - 1; i++, cornerId = (cornerId + 1) % 4)
        {
            Pixel currentPixel(contour[i].x, contour[i].y);
            vertices.push_back(currentPixel.corners[cornerId]);

            Pixel nextPixel = Pixel(contour[i + 1].x, contour[i + 1].y);
            int nextCornerId;
            while ((nextCornerId = nextPixel.getNextCornerIndex(vertices.back())) == -1)
            {
                cornerId = (cornerId + 1) % 4;
                vertices.push_back(currentPixel.corners[cornerId]);
            }
            cornerId = nextCornerId;
            if (vertices.back() != nextPixel.corners[cornerId])
                vertices.push_back(nextPixel.corners[cornerId]);
        }

        vertices.emplace_back(contour.back().x, contour.back().y);

        return CollisionRing(vertices);
    }
}
}