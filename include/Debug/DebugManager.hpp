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

#include "Core/GameLoopParticipant.hpp"
#include "Debug/DebugRenderer.hpp"
#include "Debug/DebugConsole.hpp"
#include "Graphics/FreeCamera.hpp"
#include "Graphics/Camera.hpp"

namespace nanowars {
namespace core {
    class Application;
}
namespace debug {

    using core::Application;
    using core::GameLoopParticipant;
    using graphics::FreeCamera;
    using graphics::Camera;

    class DebugManager : public GameLoopParticipant
    {
    public:
        DebugManager(Application& application);

        void update(float dt) override;
        void render(RenderWindow& window) override;

        bool handleEvent(const Event& event) override;
        bool handleContinuousEvent(const Mouse& mouse, const Keyboard& keyboard) override;

        inline DebugRenderer& getDebugRenderer() { return m_debugRenderer; }
        inline DebugConsole& getDebugConsole() { return m_debugConsole; }

    private:
        Application& m_application;
        DebugConsole m_debugConsole;
        DebugRenderer m_debugRenderer;
        FreeCamera m_freeCamera;

        void initializeCommands();
        void toggleFreeCamera(DebugConsole::args_t);
        void toggleDebugDraw(DebugConsole::args_t);
    };
}
}