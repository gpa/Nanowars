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

#include "Math/CollisionRing.hpp"

namespace nanowars {
namespace math {

    CollisionRing::CollisionRing()
    {
    }

    CollisionRing::CollisionRing(vector<Vector2f> vertices)
        : m_vertices(vertices.data(), vertices.data() + vertices.size())
    {
    }

	CollisionRing::CollisionRing(vector<Vector2i> vertices)
    {
		m_vertices.reserve(vertices.size());
        for (const auto& v : vertices)
            m_vertices.push_back(Vector2f(static_cast<float>(v.x), static_cast<float>(v.y)));
    }


    CollisionRing::CollisionRing(Vector2f* vertices, Vector2f* verticesEnd)
        : m_vertices(vertices, verticesEnd)
    {
    }

    CollisionRing::CollisionRing(boost_ring_t& vertices)
        : m_vertices(vertices)
    {
    }

    CollisionRing CollisionRing::getSimplified(float factor) const
    {
        boost_ring_t simplified;
        boost::geometry::simplify(m_vertices, simplified, factor);
        return CollisionRing(simplified);
    }

    vector<CollisionRing> CollisionRing::getDifference(const CollisionRing& collisionRing) const
    {
        vector<boost_ring_t> subtractionResult;
        boost::geometry::difference(m_vertices, collisionRing.m_vertices, subtractionResult);

        vector<CollisionRing> collisionRings;
        collisionRings.reserve(subtractionResult.size());

        for (auto& boostResult : subtractionResult)
            collisionRings.push_back(CollisionRing(boostResult));

        return collisionRings;
    }

    AABB CollisionRing::getAABB() const
    {
        return boost::geometry::return_envelope<AABB>(m_vertices);
    }

    double CollisionRing::getArea() const
    {
        return boost::geometry::area(m_vertices);
    }

    bool CollisionRing::intersects(const AABB& aabb) const
    {
        return boost::geometry::intersects(getAABB(), aabb);
    }

    void CollisionRing::correct()
    {
        boost::geometry::correct(m_vertices);
    }

    bool CollisionRing::intersects(const CollisionRing& collisionRing) const
    {
        return boost::geometry::intersects(m_vertices, collisionRing.m_vertices);
    }
}
}