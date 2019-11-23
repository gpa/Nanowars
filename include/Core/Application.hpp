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

#include "Config/PersistentConfigManager.hpp"
#include "Core/GameLoopParticipant.hpp"
#include "Globalization/TranslationManager.hpp"
#include "Asset/AssetManager.hpp"
#include "Debug/DebugManager.hpp"
#include "GUI/GUIManager.hpp"
#include "Game/GameManager.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <memory>

namespace nanowars {
namespace core {

    using sf::RenderWindow;
    using sf::Keyboard;
    using sf::Mouse;

    using std::unique_ptr;
    using std::vector;

    using namespace asset;
    using namespace config;
    using namespace game;
    using namespace gui;
    using namespace debug;
    using namespace globalization;

    class Application
    {
    public:
        Application();
        void run();

        const RenderWindow& getWindow() const;
        const AssetManager& getAssetManager() const;
        const TranslationManager& getTranslationManager() const;
        const PersistentConfigManager& getConfigManager() const;
        const DebugManager& getDebugManager() const;
        const GameManager& getGameManager() const;

        RenderWindow& getWindow();
        AssetManager& getAssetManager();
        TranslationManager& getTranslationManager();
        PersistentConfigManager& getConfigManager();
        DebugManager& getDebugManager();
        GameManager& getGameManager();

    private:
        void initialize();
        void shutdown();

        void step(float dt);
        void handleEvents();
        void render();

        RenderWindow m_window;

        PersistentConfigManager m_configManager;
        AssetManager m_assetManager;
        GameManager m_gameManager;
        GUIManager m_guiManager;
        DebugManager m_debugManager;

        vector<GameLoopParticipant*> m_gameLoopParticipants;

        Mouse m_mouse;
        Keyboard m_keyboard;
        TranslationManager m_TranslationManager;

        friend class debug::DebugManager;
    };
}
}