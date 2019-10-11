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

#include "Debug/DebugGameScreen.hpp"
#include "Util/Box2DConverter.hpp"

namespace nanowars {
namespace debug {

    using namespace util;

    DebugGameScreen::DebugGameScreen(b2World& world)
        : m_world(world)
        , m_cacheCircle(sf::CircleShape())
        , m_window(nullptr)
    {
        m_freeCameraEnabled = false;
        m_debugViewEnabled = false;
    }

    void DebugGameScreen::update(float dt)
    {
    }

    bool DebugGameScreen::handleEvent(const Event& event)
    {
        if (m_freeCameraEnabled)
            return m_freeCamera.handleEvent(event);

        return false;
    }

    bool DebugGameScreen::handleContinuousEvent(const Mouse& mouse, const Keyboard& keyboard)
    {
        return false;
    }

    void DebugGameScreen::render(RenderWindow& window)
    {
        m_window = &window;
        m_world.SetDebugDraw(this);
        m_world.DrawDebugData();
    }

    void DebugGameScreen::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
    {
        sf::ConvexShape polygon(vertexCount);
        sf::Vector2f center;
        for (int i = 0; i < vertexCount; i++)
        {
            sf::Vector2f transformedVec = Box2DConverter::toSfmlVector(vertices[i]);
            polygon.setPoint(i, sf::Vector2f(std::floor(transformedVec.x), std::floor(transformedVec.y)));
        }
        polygon.setFillColor(sf::Color::Transparent);
        polygon.setOutlineColor(sf::Color::Green);
        polygon.setOutlineThickness(1.0f);
        m_window->draw(polygon);
    }

    void DebugGameScreen::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
    {
        sf::ConvexShape polygon(vertexCount);
        for (int i = 0; i < vertexCount; i++)
        {
            sf::Vector2f transformedVec = Box2DConverter::toSfmlVector(vertices[i]);
            polygon.setPoint(i, sf::Vector2f(std::floor(transformedVec.x), std::floor(transformedVec.y)));
        }

        polygon.setFillColor(Box2DConverter::Box2DConverter::toSfmlColor(color, 60));
        polygon.setOutlineColor(sf::Color::Green);
        polygon.setOutlineThickness(1.0f);
        m_window->draw(polygon);
    }

    void DebugGameScreen::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
    {
        float scale = constants::meterToPixelRatio;
        if (m_cacheCircle.getRadius() != radius * scale)
            m_cacheCircle.setRadius(radius * scale);

        if (m_cacheCircle.getOutlineThickness() != -1.f)
        {
            m_cacheCircle.setOutlineThickness(-1.f);
            m_cacheCircle.setOutlineColor(Box2DConverter::toSfmlColor(color));
        }

        m_cacheCircle.setOrigin(radius * scale, radius * scale);
        m_cacheCircle.setPosition(Box2DConverter::toSfmlVector(center));
        m_cacheCircle.setFillColor(Box2DConverter::toSfmlColor(color));

        m_window->draw(m_cacheCircle);
    }

    void DebugGameScreen::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
    {
        float scale = constants::meterToPixelRatio;
        m_cacheCircle.setRadius(radius * scale);
        m_cacheCircle.setOrigin(radius * scale, radius * scale);
        m_cacheCircle.setPosition(Box2DConverter::toSfmlVector(center));
        m_cacheCircle.setFillColor(Box2DConverter::toSfmlColor(color, 60));
        m_cacheCircle.setOutlineThickness(1.f);
        m_cacheCircle.setOutlineColor(Box2DConverter::toSfmlColor(color));

        sf::Vertex line[2] = {
            sf::Vertex(Box2DConverter::toSfmlVector(center), Box2DConverter::toSfmlColor(color)),
            sf::Vertex(Box2DConverter::toSfmlVector(center + radius * axis), Box2DConverter::toSfmlColor(color)),
        };

        m_window->draw(m_cacheCircle);
        m_window->draw(line, 2, sf::Lines);
    }

    void DebugGameScreen::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
    {
        sf::Vertex line[] = { sf::Vertex(Box2DConverter::toSfmlVector(p1), Box2DConverter::toSfmlColor(color)),
            sf::Vertex(Box2DConverter::toSfmlVector(p2), Box2DConverter::toSfmlColor(color)) };

        m_window->draw(line, 2, sf::Lines);
    }

    void DebugGameScreen::DrawTransform(const b2Transform& xf)
    {
        float lineLength = 0.55f;

        sf::Vertex redLine[] = {
            sf::Vertex(Box2DConverter::toSfmlVector(xf.p), sf::Color::Red),
            sf::Vertex(Box2DConverter::toSfmlVector(xf.p + lineLength * xf.q.GetXAxis()), sf::Color::Red)
        };

        sf::Vertex greenLine[] = {
            sf::Vertex(Box2DConverter::toSfmlVector(xf.p), sf::Color::Green),
            sf::Vertex(Box2DConverter::toSfmlVector(xf.p + lineLength * xf.q.GetYAxis()), sf::Color::Green)
        };

        m_window->draw(redLine, 2, sf::Lines);
        m_window->draw(greenLine, 2, sf::Lines);
    }

    void DebugGameScreen::DrawParticles(const b2Vec2* centers, float32 radius, const b2ParticleColor* colors, int32 count)
    {
        m_cacheCircle.setRadius(radius * constants::meterToPixelRatio);
        m_cacheCircle.setOrigin(m_cacheCircle.getRadius() * 0.5f, m_cacheCircle.getRadius() * 0.5f);
        m_cacheCircle.setOutlineThickness(0);

        if (colors == nullptr)
            m_cacheCircle.setFillColor(sf::Color::Red);
        else
            m_cacheCircle.setFillColor(
                sf::Color(colors->r, colors->g, colors->b, colors->a));

        for (int i = 0; i < count; ++i)
        {
            m_cacheCircle.setPosition(centers->x * constants::meterToPixelRatio, centers->y * constants::meterToPixelRatio);

            m_window->draw(m_cacheCircle);
            centers++;

            if (colors != nullptr)
                colors++;
        }
    }
}
}
