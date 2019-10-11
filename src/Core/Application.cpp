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

#include "Core/Application.hpp"
#include "Core/Constants.hpp"
#include "Core/ApplicationInitializer.hpp"
#include "Config/UserConfiguration.hpp"
#include "Asset/AssetPathResolver.hpp"

namespace nanowars {
namespace core {

    using namespace sf;

    Application::Application()
        : m_configManager(constants::userConfigFilename)
        , m_assetManager(AssetPathResolver())
        , m_debugConsole(*this)
    {
        init();
    }

    void Application::init()
    {
        userConfiguration::populateWithDefaultValues(m_configManager);
        m_configManager.load();

        ApplicationInitializer initializer;
        initializer.initWindow(m_window, m_configManager);
        initializer.initScreens(m_screens, m_assetManager);
        m_debugConsole.execute("debug");
        m_debugConsole.execute("camera");
    }

    void Application::run()
    {
        Clock timer;
        while (m_window.isOpen())
        {
            float elapsed = timer.restart().asSeconds();
            step(elapsed);
            render();
        }
    }

    void Application::step(float dt)
    {
        handleEvents();
        for (auto& screen : m_screens)
            screen->update(dt);
    }

    void Application::handleEvents()
    {
        Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                shutdown();
            else
            {
                for (auto& screen : m_screens)
                {
                    if (screen->handleEvent(event))
                        break;
                }
            }
        }

        for (auto& screen : m_screens)
        {
            if (screen->handleContinuousEvent(m_mouse, m_keyboard))
                break;
        }
    }

    void Application::render()
    {
        m_window.clear(sf::Color(128, 128, 128));

        for (auto& screen : m_screens)
            screen->render(m_window);

        m_window.display();
    }

    void Application::shutdown()
    {
        m_window.close();
    }
}
}