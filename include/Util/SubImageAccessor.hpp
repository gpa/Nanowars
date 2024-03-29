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

#include "Util/ImageAccessor.hpp"
#include <SFML/Graphics/Rect.hpp>

namespace nanowars {
namespace util {

    class SubImageAccessor : public ImageAccessor
    {
    public:
        SubImageAccessor(const ImageAccessor& originalAccessor, sf::Rect<unsigned> region);
        Vector2u getSize() const override;
        Color getPixel(unsigned x, unsigned y) const override;

    private:
        const ImageAccessor& m_originalAccessor;
        const sf::Rect<unsigned> m_region;
    };
}
}