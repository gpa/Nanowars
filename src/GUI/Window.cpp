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
        : sfg::Window(sfg::Window::Style::NO_STYLE)
        , m_guiManager(guiManager)
        , m_assetHolder(std::move(assetHolder))
    {
    }

    void Window::initialize()
    {
    }

    void Window::onTopMostGained(shared_ptr<Window> previousTopMost)
    {
        SetState(sfg::Widget::State::NORMAL);
    }

    void Window::onTopMostLost(shared_ptr<Window> currentTopMost)
    {
        SetState(sfg::Widget::State::INSENSITIVE);
    }

    string Window::tx(StringTranslation translationId)
    {
        auto& tm = m_guiManager.getApplication().getTranslationManager();
        return tm.getTranslation(translationId);
    }
}
}