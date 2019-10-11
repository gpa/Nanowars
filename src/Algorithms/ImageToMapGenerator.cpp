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

#include "Algorithms/ImageToMapGenerator.hpp"
#include "Algorithms/ContourTracer.hpp"
#include "Algorithms/ContourToCollisionRingConverter.hpp"
#include "Util/SubImageAccessor.hpp"

#include <cmath>

namespace nanowars {
namespace algorithms {

    ImageToMapGenerator::ImageToMapGenerator(Vector2f divisionFactor, float simplificationFactor)
        : m_divisionFactor(divisionFactor)
        , m_simplificationFactor(simplificationFactor)
    {
    }

    vector<CollisionRing> ImageToMapGenerator::getCollisionRings(const ImageAccessor& imageAccessor) const
    {
        int imageSizeX = imageAccessor.getSize().x;
        int imageSizeY = imageAccessor.getSize().y;

        int regionWidth = m_divisionFactor.x * imageSizeX;
        int regionHeight = m_divisionFactor.y * imageSizeY;

        int regionCountX = imageSizeX / regionWidth + 1;
        int regionCountY = imageSizeY / regionHeight + 1;

        vector<CollisionRing> collisionRings;

        for (int y = 0; y < regionCountY; ++y)
        {
            for (int x = 0; x < regionCountX; ++x)
            {
                IntRect region(x * regionWidth, y * regionHeight, regionWidth, regionHeight);

                if (region.left + region.width > imageSizeX)
                    region.width = imageSizeX - region.left;

                if (region.top + region.height > imageSizeY)
                    region.height = imageSizeY - region.top;

                auto subImageAccessor
                    = SubImageAccessor(imageAccessor, region);
                auto contours = ContourTracer::findContours(subImageAccessor);

                for (auto& contour : contours)
                {
                    for (int i = 0; i < contour.size(); ++i)
                    {
                        contour[i].x += region.left;
                        contour[i].y += region.top;
                    }

                    auto collisionRing = ContourToCollisionRingConverter::convert(contour);
                    auto simplified = collisionRing.getSimplified(0.7f);
                    collisionRings.push_back(simplified);
                }
            }
        }

        return collisionRings;
    }
}
}