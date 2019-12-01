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
#include "Util/ImageAccessor.hpp"
#include "Util/Matrix.hpp"

#include <vector>

namespace nanowars {
namespace algorithms {

    using math::Vector2u;
    using math::Vector2i;
    using util::Matrix;
    using util::ImageAccessor;
    using std::vector;

    class ContourTracer
    {
    public:
        typedef vector<Vector2u> contour_t;
        static vector<contour_t> findContours(const ImageAccessor& image);

    private:
        ContourTracer(const ImageAccessor& image);

        vector<contour_t> findAllContours();
        contour_t followContour(int startX, int startY, int16_t contourId, bool isInternal = false);

        inline bool isSolid(unsigned x, unsigned y) const { return m_image.getPixel(x, y).a > 128; }
        inline bool isSolid(Vector2i p) const { return isSolid(p.x, p.y); }
        inline bool isOutOfBounds(int x, int y) const { return x < 0 || (static_cast<unsigned>(x) >= m_size.x || y < 0 || static_cast<unsigned>(y) >= m_size.y); }
        inline bool isOutOfBounds(unsigned x, unsigned y) const { return x < 0 || x >= m_size.x || y < 0 || y >= m_size.y; }
		inline bool isOutOfBounds(Vector2i p) const { return isOutOfBounds(p.x, p.y); }
        inline bool isNone(int16_t pixelId) const { return pixelId == 0; }

        const ImageAccessor& m_image;
        const Vector2u m_size;
        Matrix<int16_t> m_contourIdByPixel;
    };
}
}