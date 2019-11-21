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
        auto mainWindow = std::shared_ptr<Window>(new MainWindow(*this, m_assetHolder.getNewHolder()));
        mainWindow->initialize();
        makeTopMost(mainWindow);
    }

    void GUIManager::update(float dt)
    {
        m_desktop.Update(dt);
    }

    bool GUIManager::handleEvent(const Event& event)
    {
        m_desktop.HandleEvent(event);
        return false;
    }

    bool GUIManager::handleContinuousEvent(const Mouse& mouse, const Keyboard& keyboard)
    {
        return false;
    }

    void GUIManager::render(RenderWindow& window)
    {
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

        m_desktop.Remove(window);
        window->onTopMostLost(current);
        current->onTopMostGained(window);
    }

    Application& GUIManager::getApplication() const
    {
        return m_application;
    }
}
}