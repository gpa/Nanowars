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

#include "Algorithms/ContourTracer.hpp"
#include <array>
namespace nanowars {
namespace algorithms {

    using math::Vector2i;

    vector<ContourTracer::contour_t> ContourTracer::findContours(const ImageAccessor& image)
    {
        ContourTracer contourTracer(image);
        return contourTracer.findAllContours();
    }

    ContourTracer::ContourTracer(const ImageAccessor& image)
        : m_image(image)
        , m_size(image.getSize())
        , m_contourIdByPixel(m_size)
    {
    }

    ContourTracer::contour_t ContourTracer::followContour(int startX, int startY, int16_t contourId, bool isInternal)
    {
        contour_t contour;
        std::array<Vector2i, 8> movements = { Vector2i{ 1, 0 }, { 1, 1 }, { 0, 1 }, { -1, 1 }, { -1, 0 }, { -1, -1 }, { 0, -1 }, { 1, -1 } };

        Vector2i startPosition(startX, startY);
        Vector2i currentPosition(startPosition);
        Vector2i orientationPixel(-1, -1);
        bool isFinished = false;
        int directionId = isInternal ? 3 : 7;

        m_contourIdByPixel.setAt((Vector2u)startPosition, contourId);
        do
        {
            contour.push_back((Vector2u)currentPosition);
            int i;
            for (i = 0; i < 8; i++, directionId = (directionId + 1) % 8)
            {
                Vector2i possiblePixel = currentPosition + movements[directionId];
                if (isOutOfBounds(possiblePixel))
                    continue;

                if (!isSolid(possiblePixel))
                {
                    m_contourIdByPixel.setAt((Vector2u)possiblePixel, -1);
                    continue;
                }

                if (orientationPixel.x < 0)
                    orientationPixel = possiblePixel;
                else
                    isFinished = currentPosition == startPosition && possiblePixel == orientationPixel;

                m_contourIdByPixel.setAt((Vector2u)possiblePixel, contourId);
                currentPosition = possiblePixel;
                break;
            }

            if (i == 8)
                isFinished = true;

            directionId = (directionId + 6) % 8;
        } while (!isFinished);

        return contour;
    }

    // based on https://www.iis.sinica.edu.tw/papers/fchang/1362-F.pdf
    vector<ContourTracer::contour_t> ContourTracer::findAllContours()
    {
        vector<contour_t> contours;
        int contourId = 1;
        for (unsigned y = 0; y < m_size.y; ++y)
        {
            for (unsigned x = 0; x < m_size.x; ++x)
            {
                if (!isSolid(x, y))
                    continue;

                bool isAboveSet = y > 0 && isSolid(x, y - 1);
                bool isBelowSet = y + 1 < m_size.y && isSolid(x, y + 1);
                int16_t currentPixelId = m_contourIdByPixel.getAt(x, y);
                int16_t belowPixelId = y + 1 < m_size.y ? m_contourIdByPixel.getAt(x, y + 1) : -1;

                if (isNone(currentPixelId) && !isAboveSet)
                {
                    const auto& contour = followContour(x, y, contourId);
                    contours.push_back(contour);
                    contourId++;
                }
                else if (isNone(belowPixelId) && !isBelowSet)
                {
                    if (isNone(currentPixelId))
                        currentPixelId = m_contourIdByPixel.getPrevious(x, y);

                    const auto& contour = followContour(x, y, currentPixelId, true);
                    contours.push_back(contour);
                }
                else if (isNone(currentPixelId))
                {
                    auto previousId = m_contourIdByPixel.getPrevious(x, y);
                    m_contourIdByPixel.setAt(x, y, previousId);
                }
            }
        }
        return contours;
    }
}
}