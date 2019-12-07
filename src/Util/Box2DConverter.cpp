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

#include "Util/Box2DConverter.hpp"
#include "Core/Constants.hpp"

namespace nanowars {
namespace util {

    using namespace core;

    CollisionRing Box2DConverter::circleToCollisionRing(b2Vec2 position, float radius, unsigned vertexCount)
    {
        vector<Vector2f> vertices;
        vertices.resize(vertexCount);

        const float theta
            = boost::math::constants::two_pi<float>() / static_cast<float>(vertices.size());

        float c = std::cos(theta);
        float s = std::sin(theta);

        float t = 0.0f;
        float y = 0.0f;
        float x = radius;
        for (size_t i = 0; i < vertices.size(); i++)
        {
            float vx = x + position.x;
            float vy = y + position.y;
            vertices[i] = Vector2f(vx, vy);
            t = x;
            x = c * x - s * y;
            y = s * t + c * y;
        }

        CollisionRing collisionRing(vertices);
        collisionRing.correct();
        return collisionRing;
    }

    sf::Color Box2DConverter::toSfmlColor(const b2Color& color, sf::Uint8 alpha)
    {
        return sf::Color(static_cast<sf::Uint8>(color.r * 255),
            static_cast<sf::Uint8>(color.g * 255),
            static_cast<sf::Uint8>(color.b * 255),
            alpha);
    }

    sf::Vector2f Box2DConverter::toSfmlVector(const b2Vec2& vector, bool scaleToPixels)
    {
        return sf::Vector2f(vector.x * constants::meterToPixelRatio, vector.y * constants::meterToPixelRatio);
    }
}
}