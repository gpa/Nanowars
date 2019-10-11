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

#include "Screens/Screen.hpp"
#include "Graphics/FollowingCamera.hpp"
#include "Controllers/KeyboardRocketController.hpp"
#include "Game/GameWorld.hpp"

namespace nanowars {
namespace debug {
    class DebugConsole;
}
}

namespace nanowars {
namespace screens {

    using namespace game;
    using namespace graphics;
    using namespace controllers;

    class GameScreen : public Screen
    {
    public:
        GameScreen(AssetHolder&& assetHolder);

        void update(float dt) override;
        void render(RenderWindow& window) override;

        bool handleEvent(const Event& event) override;
        bool handleContinuousEvent(const Mouse& mouse, const Keyboard& keyboard) override;

    private:
        GameWorld m_gameWorld;

        Camera* m_activeCamera;
        FollowingCamera m_followingCamera;

        KeyboardRocketController m_keyboardRocketController;

        friend class debug::DebugConsole;
    };
}
}