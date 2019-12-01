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
#include <memory>

namespace nanowars {
namespace util {

    using math::Vector2u;
    using std::unique_ptr;

    template <typename T>
    class Matrix
    {

    public:
        Matrix(Vector2u size)
            : m_size(size)
            , m_array(new T[size.x * size.y])
        {
            for (unsigned long i = 0; i < size.x * size.y; ++i)
                m_array[i] = 0;
        }

        inline T getAt(Vector2u pos) const { return m_array[index(pos.x, pos.y)]; }
        inline T getAt(int x, int y) const { return m_array[index(x, y)]; }
        inline T getPrevious(int x, int y) const { return x - 1 >= 0 ? m_array[index(x, y)] : m_array[index(0, y - 1)]; }

        inline void setAt(int x, int y, T value) const { m_array[index(x, y)] = value; }
        inline void setAt(Vector2u pos, T value) const { m_array[index(pos.x, pos.y)] = value; }

        inline Vector2u getSize() const { return m_size; }

    protected:
        inline int index(int x, int y) const { return x + m_size.x * y; }

    private:
        unique_ptr<T[]> m_array;
        Vector2u m_size;
    };
}
}