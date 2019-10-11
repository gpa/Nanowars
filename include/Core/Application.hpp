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
#include "Assets/AssetManager.hpp"
#include "Screens/Screen.hpp"
#include "Debug/DebugConsole.hpp"

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

    using namespace assets;
    using namespace config;
    using namespace screens;

    class Application
    {
    public:
        Application();
        void run();

    private:
        void init();
        void shutdown();

        void step(float dt);
        void handleEvents();
        void render();

        RenderWindow m_window;

        vector<unique_ptr<Screen>> m_screens;

        PersistentConfigManager m_configManager;
        AssetManager m_assetManager;

        Mouse m_mouse;
        Keyboard m_keyboard;

        debug::DebugConsole m_debugConsole;
        friend class debug::DebugConsole;
    };
}
}