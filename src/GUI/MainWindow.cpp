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

#include "GUI/MainWindow.hpp"
#include "GUI/GUIManager.hpp"
#include "Core/Constants.hpp"
#include "Core/Application.hpp"
#include "Globalization/TranslationManager.hpp"
#include "GUI/SettingsWindow.hpp"

#include <SFGUI/Widgets.hpp>

namespace nanowars {
namespace gui {

    using namespace globalization;

    MainWindow::MainWindow(GUIManager& guiManager, AssetHolder&& assetHolder)
        : Window(guiManager, std::move(assetHolder))
    {
        m_window->SetStyle(sfg::Window::Style::NO_STYLE);
        m_window->SetRequisition(sf::Vector2f(400, 600));

        auto onlineButton = sfg::Button::Create(tx(StringTranslation_OnlineGame));
        auto lanButton = sfg::Button::Create(tx(StringTranslation_LanGame));
        auto localButton = sfg::Button::Create(tx(StringTranslation_LocalGame));
        auto settingsButton = sfg::Button::Create(tx(StringTranslation_Settings));
        auto quitButton = sfg::Button::Create(tx(StringTranslation_Quit));

        auto layoutBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 15.f);
        auto logo = sfg::Label::Create(core::constants::windowTitle);
        logo->SetId("logo");
        layoutBox->Pack(logo, false, false);

        auto menuBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 15.f);
        menuBox->Pack(onlineButton);
        menuBox->Pack(lanButton);
        menuBox->Pack(localButton);
        menuBox->Pack(settingsButton);
        menuBox->Pack(quitButton);

        onlineButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainWindow::onOnlineButtonClicked, this));
        lanButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainWindow::onLanButtonClicked, this));
        localButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainWindow::onLocalButtonClicked, this));
        settingsButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainWindow::onSettingsButtonClicked, this));
        quitButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainWindow::onQuitButtonClicked, this));

        layoutBox->Pack(menuBox);
        m_window->Add(layoutBox);
    }

    void MainWindow::update(float dt)
    {
        center();
        Window::update(dt);
    }

    void MainWindow::handleEvent(const sf::Event& event)
    {
        Window::handleEvent(event);
    }

    void MainWindow::onOnlineButtonClicked()
    {
    }

    void MainWindow::onLanButtonClicked()
    {
    }

    void MainWindow::onLocalButtonClicked()
    {
    }

    void MainWindow::onSettingsButtonClicked()
    {
        auto settingsWindow = std::shared_ptr<gui::SettingsWindow>(new SettingsWindow(m_guiManager, m_assetHolder.getNewHolder()));
        m_guiManager.makeTopMost(settingsWindow);
    }

    void MainWindow::onQuitButtonClicked()
    {
    }
}
}