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

#include "GUI/GUIManager.hpp"
#include "Core/Application.hpp"

#include "GUI/MainWindow.hpp"
#include "GUI/Window.hpp"
#include "GUI/ConsoleWindow.hpp"

namespace nanowars {
namespace gui {

    GUIManager::GUIManager(Application& application, AssetHolder&& assetHolder)
        : m_assetHolder(std::move(assetHolder))
        , m_application(application)
    {
        m_desktop.SetProperty("#logo", "FontSize", 105);
    }

    void GUIManager::initializeWindows()
    {
        spawnMainMenu();
        m_inputManager.addBinding(Event::EventType::KeyReleased, Keyboard::Key::Escape, std::bind(&GUIManager::spawnMainMenu, this));
        m_inputManager.addBinding(Event::EventType::KeyReleased, Keyboard::Key::Tilde, std::bind(&GUIManager::spawnDebugConsole, this));
        m_inputManager.addBinding(Event::EventType::Closed, std::bind(&GUIManager::closeWindow, this));
    }

    void GUIManager::update(float dt)
    {
        m_desktop.Update(dt);
    }

    void GUIManager::handleInput(InputQueue& inputQueue)
    {
        if (m_windows.size() > 0)
        {
            while (inputQueue.hasEvent())
            {
                auto& event = inputQueue.getEvent();
                if (event.type == Event::EventType::Closed)
                    closeWindow();
                else
                    m_desktop.HandleEvent(event);

                inputQueue.consumeEvent();
            }

            inputQueue.consumeRealtimeKeyboardInput();
            inputQueue.consumeRealtimeMouseInput();
            processRemoved();
        }

        m_inputManager.processInput(inputQueue);
    }

    void GUIManager::render(RenderWindow& window)
    {
        window.resetGLStates();
        m_sfgui.Display(window);
    }

    void GUIManager::makeTopMost(shared_ptr<Window> window)
    {
        auto previous = shared_ptr<Window>();
        if (!m_windows.empty())
        {
            previous = m_windows.back();
            m_windows.push_back(window);
            previous->onTopMostLost(window);
        }
        else
        {
            m_windows.push_back(window);
        }

        m_desktop.Add(window);
        window->onTopMostGained(previous);
    }

    void GUIManager::removeTopMost()
    {
        shared_ptr<Window> window = m_windows.back();
        m_windows.pop_back();

        auto current = shared_ptr<Window>();
        if (!m_windows.empty())
            current = m_windows.back();

        m_removed.push_back(window);
        window->onTopMostLost(current);

        if (current.get() != nullptr)
            current->onTopMostGained(window);
    }

    void GUIManager::processRemoved()
    {
        for (auto& window : m_removed)
            m_desktop.Remove(window);

        m_removed.clear();
    }

    void GUIManager::spawnMainMenu()
    {
        auto mainWindow = std::shared_ptr<MainWindow>(new MainWindow(*this, m_assetHolder.getNewHolder()));
        makeTopMost(mainWindow);
    }

    void GUIManager::spawnDebugConsole()
    {
        auto& debugConsole = m_application.getDebugManager().getDebugConsole();
        auto consoleWindow = std::shared_ptr<ConsoleWindow>(new ConsoleWindow(*this, m_assetHolder.getNewHolder(), debugConsole));
        makeTopMost(consoleWindow);
    }

    void GUIManager::closeWindow()
    {
        m_application.getWindow().close();
    }

    RenderWindow& GUIManager::getWindow()
    {
        return m_application.getWindow();
    }

    PersistentConfigManager& GUIManager::getConfigManager()
    {
        return m_application.getConfigManager();
    }

    GameManager& GUIManager::getGameManager()
    {
        return m_application.getGameManager();
    }

    TranslationManager& GUIManager::getTranslationManager()
    {
        return m_application.getTranslationManager();
    }
}
}