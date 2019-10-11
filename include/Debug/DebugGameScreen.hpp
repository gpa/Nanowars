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

#include "Game/GameWorld.hpp"
#include "Screens/Screen.hpp"
#include "Screens/GameScreen.hpp"
#include "Graphics/FreeCamera.hpp"
#include "Core/Constants.hpp"

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <cmath>

namespace nanowars {
namespace debug {

    using namespace screens;
    using namespace core;
    using namespace graphics;

    class DebugGameScreen : public b2Draw, public Screen
    {
    public:
        DebugGameScreen(b2World& gameWorld);

        void setFreeCameraEnabled(bool enabled);
        bool getFreeCameraEnabled() const;

        void setDebugViewEnabled(bool enabled);
        bool getDebugViewEnabled() const;

        FreeCamera& getFreeCamera();

        void update(float dt) override;
        bool handleEvent(const Event& event) override;
        bool handleContinuousEvent(const Mouse& mouse, const Keyboard& keyboard) override;
        void render(RenderWindow& window) override;

        void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
        void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
        void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override;
        void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override;
        void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
        void DrawTransform(const b2Transform& xf) override;
        virtual void DrawParticles(const b2Vec2* centers, float32 radius, const b2ParticleColor* colors, int32 count) override;

    private:
        b2World& m_world;
        FreeCamera m_freeCamera;

        bool m_freeCameraEnabled;
        bool m_debugViewEnabled;

        sf::RenderTarget* m_window;
        sf::CircleShape m_cacheCircle;
    };

    inline void DebugGameScreen::setFreeCameraEnabled(bool enabled)
    {
        m_freeCameraEnabled = enabled;
    }

    inline bool DebugGameScreen::getFreeCameraEnabled() const
    {
        return m_freeCameraEnabled;
    }

    inline FreeCamera& DebugGameScreen::getFreeCamera()
    {
        return m_freeCamera;
    }

    inline void DebugGameScreen::setDebugViewEnabled(bool enabled)
    {
        m_debugViewEnabled = enabled;
    }

    inline bool DebugGameScreen::getDebugViewEnabled() const
    {
        return m_debugViewEnabled;
    }
}
}