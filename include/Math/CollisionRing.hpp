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

#include "Math/AABB.hpp"
#include "Math/Vector2.hpp"
#include "Util/BoostLibraryConfig.hpp"

#include <Box2D/Box2D.h>
#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/geometry.hpp>

#include <vector>

namespace nanowars {
namespace math {

    using std::vector;

    class CollisionRing
    {
    public:
        CollisionRing();
        CollisionRing(vector<Vector2f> vertices);
        CollisionRing(vector<Vector2i> vertices);
        CollisionRing(Vector2f* vertices, Vector2f* verticesEnd);

        inline size_t getCount() const { return m_vertices.size(); }
        inline const Vector2f* getVertices() const { return m_vertices.data(); }

        AABB getAABB() const;
        double getArea() const;

        CollisionRing getSimplified(float factor) const;
        vector<CollisionRing> getDifference(const CollisionRing& collisionRing) const;

        bool intersects(const AABB& aabb) const;
        bool intersects(const CollisionRing& collisionRing) const;

        inline Vector2f& operator[](size_t index) { return m_vertices[index]; }

        void correct();

    private:
        typedef boost::geometry::model::ring<Vector2f, false, true> boost_ring_t;
        CollisionRing(boost_ring_t& vertices);

        boost_ring_t m_vertices;
    };
}
}