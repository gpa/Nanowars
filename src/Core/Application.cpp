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
        , m_gameManager(m_assetManager.getNewHolder(), m_configManager)
        , m_debugManager(*this)
        , m_guiManager(*this, m_assetManager.getNewHolder())
        , m_translationManager(AssetPathResolver(), constants::defaultLanguage)
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
        for (auto iter = m_gameLoopParticipants.rbegin(); iter != m_gameLoopParticipants.rend(); ++iter)
            (*iter)->update(dt);
    }

    void Application::handleEvents()
    {
        m_inputQueue.consume(m_window);
        for (auto iter = m_gameLoopParticipants.rbegin(); iter != m_gameLoopParticipants.rend(); ++iter)
        {
            (*iter)->handleInput(m_inputQueue);
            m_inputQueue.resetPosition();
        }
    }

    void Application::render()
    {
        m_window.clear(constants::BackgroundColor);

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
        return m_translationManager;
    }

    const DebugManager& Application::getDebugManager() const
    {
        return m_debugManager;
    }

    const GameManager& Application::getGameManager() const
    {
        return m_gameManager;
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
        return m_translationManager;
    }

    DebugManager& Application::getDebugManager()
    {
        return m_debugManager;
    }

    GameManager& Application::getGameManager()
    {
        return m_gameManager;
    }
}
}