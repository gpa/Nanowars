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

#include "GUI/ConsoleWindow.hpp"
#include "Core/Application.hpp"

namespace nanowars {
namespace gui {

    using namespace sfg;

    FixedPositionWindow::FixedPositionWindow(GUIManager& guiManager, AssetHolder&& assetHolder)
        : Window(guiManager, std::move(assetHolder))
    {
    }

    void FixedPositionWindow::HandleUpdate(float dt)
    {
        // It would be much nicer to do this on events instead of here
        // but events are only passed to the topmost window leaving
        // the below windows un-updated. Doing this in the update step
        // also takes care of disallowing moving the window which is also nice.
        updatePosition();
        Window::HandleUpdate(dt);
    }

    void FixedPositionWindow::initialize()
    {
        updatePosition();
        Window::initialize();
    }

    void FixedPositionWindow::centerHorizontally()
    {
        auto s = m_guiManager.getApplication().getWindow().getSize();
        auto ls = GetAllocation();
        SetPosition(sf::Vector2f((s.x / 2) - (ls.width / 2), ls.top));
    }

    void FixedPositionWindow::centerVertically()
    {
        auto s = m_guiManager.getApplication().getWindow().getSize();
        auto ls = GetAllocation();
        SetPosition(sf::Vector2f(ls.left, (s.y / 2) - (ls.height / 2)));
    }

    void FixedPositionWindow::updatePosition()
    {
        if (m_positionFlags & FixedPosition::CenterHorizontally)
            centerHorizontally();

        if (m_positionFlags & FixedPosition::CenterVertically)
            centerVertically();
    }

    void FixedPositionWindow::setFixedPosition(int positionFlags)
    {
        m_positionFlags = positionFlags;
    }

    int FixedPositionWindow::getFixedPosition()
    {
        return m_positionFlags;
    }
}
}