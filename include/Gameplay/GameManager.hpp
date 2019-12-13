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
#include "Graphics/GameRenderer.hpp"
#include "Input/ControllerAwareInputManager.hpp"
#include "Config/ConfigManager.hpp"
#include "Gameplay/Games/Game.hpp"
#include "Gameplay/Players/Player.hpp"
#include "Gameplay/Controllers/EntityController.hpp"

#include <SFML/Graphics.hpp>

namespace nanowars {
namespace debug {
    class DebugConsole;
}
namespace gameplay {

    using namespace gameplay;
    using namespace core;
    using namespace graphics;
    using namespace controllers;
    using namespace config;
    using namespace input;
    using namespace players;
    using namespace games;
    using namespace sf;

    class GameManager : public GameLoopParticipant
    {
    public:
        GameManager(AssetHolder&& assetHolder, const ConfigManager& configManager);

        void update(float dt) override;
        void render(RenderWindow& window) override;
        void handleInput(InputQueue& inputQueue) override;

        void setGame(GameInfo gameInfo);
        const GameInfo& getGame() const;

        void updateControllers();
    private:
        shared_ptr<Game> m_game;
        vector<shared_ptr<EntityController>> m_controllers;
        
        GameRenderer m_gameRenderer;
        AssetHolder m_assetHolder;
        
        const ConfigManager& m_configManager;
        ControllerAwareInputManager m_inputManager;

        GameInfo m_noGameInfo;
        friend class debug::DebugManager;
    };
}
}