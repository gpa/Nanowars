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
#include "Globalization/TranslationManager.hpp"
#include "GUI/SettingsWindow.hpp"
#include "GUI/ConfirmationWindow.hpp"

#include <SFGUI/Widgets.hpp>

namespace nanowars {
namespace gui {

    using namespace globalization;

    MainWindow::MainWindow(GUIManager& guiManager, AssetHolder&& assetHolder)
        : FixedPositionWindow(guiManager, std::move(assetHolder))
    {
    }

    void MainWindow::initialize()
    {
        RequestResize();
        SetStyle(sfg::Window::Style::NO_STYLE);
        SetRequisition(sf::Vector2f(400, 700));

        auto settingsButton = sfg::Button::Create(tx(StringTranslation::Settings));
        auto quitButton = sfg::Button::Create(tx(StringTranslation::ExitNanowars));

        auto layoutBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 50.f);
        auto logo = sfg::Label::Create(core::constants::windowTitle);
        logo->SetId("logo");
        layoutBox->Pack(logo, false, false);

        auto menuBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 15.f);

        auto gameState = m_guiManager.getGameManager().getGame().state;
        if (gameState == GameState::InProgress || gameState == GameState::Paused)
        {
            auto resumeButton = sfg::Button::Create(tx(StringTranslation::Resume));
            auto quitToMainMenuButton = sfg::Button::Create(tx(StringTranslation::ReturnToMainMenu));

            menuBox->Pack(resumeButton);
            menuBox->Pack(settingsButton);
            menuBox->Pack(quitToMainMenuButton);
            menuBox->Pack(quitButton);

            resumeButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainWindow::onResumeButtonClicked, this));
            quitToMainMenuButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainWindow::onReturnToMainMenuButtonClicked, this));
        }
        else
        {
            auto onlineButton = sfg::Button::Create(tx(StringTranslation::OnlineGame));
            auto lanButton = sfg::Button::Create(tx(StringTranslation::LanGame));
            auto localButton = sfg::Button::Create(tx(StringTranslation::LocalGame));

            menuBox->Pack(onlineButton);
            menuBox->Pack(lanButton);
            menuBox->Pack(localButton);
            menuBox->Pack(settingsButton);
            menuBox->Pack(quitButton);

            onlineButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainWindow::onOnlineButtonClicked, this));
            lanButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainWindow::onLanButtonClicked, this));
            localButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainWindow::onLocalButtonClicked, this));
        }

        settingsButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainWindow::onSettingsButtonClicked, this));
        quitButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainWindow::onExitButtonClicked, this));

        layoutBox->Pack(menuBox);
        Add(layoutBox);
        setFixedPosition(FixedPosition::CenterVertically | FixedPosition::CenterHorizontally);
        FixedPositionWindow::initialize();
    }

    void MainWindow::HandleEvent(const Event& event)
    {
        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Key::Escape)
            {
                if (m_guiManager.getGameManager().getGame().state == GameState::InProgress)
                    m_guiManager.removeTopMost();
            }
        }

        FixedPositionWindow::HandleEvent(event);
    }

    void MainWindow::onOnlineButtonClicked()
    {
        GameInfo gameInfo;
        gameInfo.type = GameType::Deathmatch;
        gameInfo.deathmatchGameInfo.respawnTimeout = 5.0f;
        gameInfo.deathmatchGameInfo.gameTimeout = 8 * 60;
        gameInfo.deathmatchGameInfo.killsTimeout = 15;
        
        gameInfo.players.push_back(std::make_shared<Player>(tx(StringTranslation::Player1)));
        gameInfo.players.push_back(std::make_shared<Player>(tx(StringTranslation::Player2)));

        m_guiManager.getGameManager().setGame(gameInfo);
        m_guiManager.removeTopMost();
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

    void MainWindow::onExitButtonClicked()
    {
        auto gameState = m_guiManager.getGameManager().getGame().state;
        if (gameState != GameState::InProgress && gameState != GameState::Paused)
        {
            exitApplication();
            return;
        }

        auto confirmationWindow = std::make_shared<ConfirmationWindow>(m_guiManager, m_assetHolder.getNewHolder(),
            tx(StringTranslation::ExitNanowars),
            tx(StringTranslation::ExitGameAndReturnToDesktop),
            tx(StringTranslation::Exit),
            tx(StringTranslation::Cancel),
            std::bind(&MainWindow::onExitConfirmation, this, std::placeholders::_1));

        m_guiManager.makeTopMost(confirmationWindow);
    }

    void MainWindow::onResumeButtonClicked()
    {
        m_guiManager.removeTopMost();
    }

    void MainWindow::onReturnToMainMenuButtonClicked()
    {
        auto confirmationWindow = std::make_shared<ConfirmationWindow>(m_guiManager, m_assetHolder.getNewHolder(),
            tx(StringTranslation::ReturnToMainMenu),
            tx(StringTranslation::ExitGameAndReturnToMainMenu),
            tx(StringTranslation::OK),
            tx(StringTranslation::Cancel),
            std::bind(&MainWindow::onReturnToMainMenuConfirmation, this, std::placeholders::_1));

        m_guiManager.makeTopMost(confirmationWindow);
    }

    void MainWindow::onReturnToMainMenuConfirmation(bool confirmed)
    {
        if (confirmed)
            exitGame();
    }

    void MainWindow::onExitConfirmation(bool confirmed)
    {
        if (confirmed)
        {
            exitApplication();
        }
    }

    void MainWindow::exitApplication()
    {
        m_guiManager.getWindow().close();
    }

    void MainWindow::exitGame()
    {
        m_guiManager.removeTopMost();
        m_guiManager.getGameManager().setGame(GameInfo(GameType::NoGame));
        auto mainWindow = std::shared_ptr<gui::MainWindow>(new MainWindow(m_guiManager, m_assetHolder.getNewHolder()));
        m_guiManager.makeTopMost(mainWindow);
    }
}
}