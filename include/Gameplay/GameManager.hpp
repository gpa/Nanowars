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
#include "Graphics/FollowingCamera.hpp"
#include "Gameplay/GameWorld.hpp"

#include <SFML/Graphics.hpp>

namespace nanowars {
namespace debug {
    class DebugConsole;
}
namespace gameplay {

    using namespace gameplay;
    using namespace core;
    using namespace graphics;
    using namespace sf;

    class GameManager : public GameLoopParticipant
    {
    public:
        GameManager(AssetHolder&& assetHolder);

        void update(float dt) override;
        void render(RenderWindow& window) override;

        bool handleEvent(const Event& event) override;
        bool handleContinuousEvent(const Mouse& mouse, const Keyboard& keyboard) override;

        void startGame();
        void exitGame();
        bool isGameRunning();

    private:
        shared_ptr<GameWorld> m_gameWorld;
        shared_ptr<Camera> m_activeCamera;
        AssetHolder m_assetHolder;
        
		friend class debug::DebugManager;
    };
}
}