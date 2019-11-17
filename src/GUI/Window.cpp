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

#include "GUI/Window.hpp"
#include "GUI/GUIManager.hpp"
#include "Core/Application.hpp"

namespace nanowars {
namespace gui {

    Window::Window(GUIManager& guiManager, AssetHolder&& assetHolder)
        : m_guiManager(guiManager)
        , m_assetHolder(std::move(assetHolder))
        , m_window(sfg::Window::Create())
    {
    }

    void Window::update(float dt)
    {
        m_window->Update(dt);
    }

    void Window::handleEvent(const Event& event)
    {
        m_window->HandleEvent(event);
    }

    void Window::onTopMostGained(shared_ptr<Window> previousTopMost)
    {
    }

    void Window::onTopMostLost(shared_ptr<Window> currentTopMost)
    {
    }

    void Window::centerHorizontally()
    {
        auto s = m_guiManager.getApplication().getWindow().getSize();
        auto ls = m_window->GetAllocation();
        m_window->SetPosition(sf::Vector2f((s.x / 2) - (ls.width / 2), ls.height));
    }

    void Window::centerVertically()
    {
        auto s = m_guiManager.getApplication().getWindow().getSize();
        auto ls = m_window->GetAllocation();
        m_window->SetPosition(sf::Vector2f(ls.width, (s.y / 2) - (ls.height / 2)));
    }

    void Window::center()
    {
        auto s = m_guiManager.getApplication().getWindow().getSize();
        auto ls = m_window->GetAllocation();

        float lx = (s.x / 2) - (ls.width / 2);
        float ly = (s.y / 2) - (ls.height / 2);

        m_window->SetPosition(sf::Vector2f(lx, ly));
    }

    void Window::setMargin(float xOffset, float yOffset)
    {
        auto s = m_guiManager.getApplication().getWindow().getSize();
        auto ms = m_window->GetAllocation();
        float mx = s.x * xOffset;
        float my = s.y * yOffset;

        m_window->SetPosition(sf::Vector2f(mx, my));
    }

    string Window::tx(StringTranslation translationId)
    {
        auto& tm = m_guiManager.getApplication().getTranslationManager();
        return tm.getTranslation(translationId);
    }
}
}