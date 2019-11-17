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
        , m_gameManager(m_assetManager.getNewHolder())
        , m_debugManager(*this)
        , m_guiManager(*this, m_assetManager.getNewHolder())
    {
        initialize();
    }

    void Application::initialize()
    {
        userConfiguration::populateWithDefaultValues(m_configManager);
        m_configManager.load();

        ApplicationInitializer initializer;
        initializer.initWindow(m_window, m_configManager);

        m_gameLoopParticipants.push_back(&m_gameManager);
        m_gameLoopParticipants.push_back(&m_debugManager);
        m_gameLoopParticipants.push_back(&m_guiManager);

        m_guiManager.initializeWindows();
        m_debugManager.getDebugConsole().execute("debug");
    }

    void Application::run()
    {
        Clock timer;
        while (m_window.isOpen())
        {
            float elapsed = timer.restart().asSeconds();
            handleEvents();
            step(elapsed);
            render();
        }
    }

    void Application::step(float dt)
    {
        for (auto* participant : m_gameLoopParticipants)
            participant->update(dt);
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
                for (auto* participant : m_gameLoopParticipants)
                {
                    if (participant->handleEvent(event))
                        break;
                }
            }
        }

        for (auto* participant : m_gameLoopParticipants)
            participant->handleContinuousEvent(m_mouse, m_keyboard);
    }

    void Application::render()
    {
        m_window.clear(sf::Color(128, 128, 128));

        for (auto* participant : m_gameLoopParticipants)
            participant->render(m_window);

        m_window.display();
    }

    void Application::shutdown()
    {
        m_window.close();
    }

    const RenderWindow& Application::getWindow() const
    {
        return m_window;
    }

    const PersistentConfigManager& Application::getConfigManager() const
    {
        return m_configManager;
    }

    const AssetManager& Application::getAssetManager() const
    {
        return m_assetManager;
    }

    const TranslationManager& Application::getTranslationManager() const
    {
        return m_TranslationManager;
    }

    const DebugManager& Application::getDebugManager() const
    {
        return m_debugManager;
    }

    RenderWindow& Application::getWindow()
    {
        return m_window;
    }

    PersistentConfigManager& Application::getConfigManager()
    {
        return m_configManager;
    }

    AssetManager& Application::getAssetManager()
    {
        return m_assetManager;
    }

    TranslationManager& Application::getTranslationManager()
    {
        return m_TranslationManager;
    }

    DebugManager& Application::getDebugManager()
    {
        return m_debugManager;
    }
}
}