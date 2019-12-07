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

#include "Util/ImageAccessorSfmlImpl.hpp"

namespace nanowars {
namespace util {

    ImageAccessorSfmlImpl::ImageAccessorSfmlImpl(const sf::Image& sfImage)
        : m_sfImage(sfImage)
    {
    }

    Vector2u ImageAccessorSfmlImpl::getSize() const
    {
        return m_sfImage.getSize();
    }

    Color ImageAccessorSfmlImpl::getPixel(unsigned x, unsigned y) const
    {
        return m_sfImage.getPixel(x, y);
    }
}
}