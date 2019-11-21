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

#include "GUI/ConfirmationWindow.hpp"
#include "GUI/GUIManager.hpp"

namespace nanowars {
namespace gui {

    ConfirmationWindow::ConfirmationWindow(GUIManager& guiManager, AssetHolder&& assetHolder, string titleString, string infoString, string acceptString, string rejectString)
        : Window(guiManager, std::move(assetHolder))
        , m_titleString(titleString)
        , m_infoString(infoString)
        , m_acceptString(acceptString)
        , m_rejectString(rejectString)
    {
    }

    void ConfirmationWindow::initialize()
    {
        m_accepted = false;
        m_rejected = false;

        SetStyle(sfg::Window::Style::BACKGROUND | sfg::Window::Style::TITLEBAR);
        SetTitle(m_titleString);
        SetRequisition(sf::Vector2f(400.f, 10.f));

        auto label = sfg::Label::Create(m_infoString);
        auto acceptButton = sfg::Button::Create(m_acceptString);
        auto rejectButton = sfg::Button::Create(m_rejectString);

        acceptButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&ConfirmationWindow::onAccepted, this));
        rejectButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&ConfirmationWindow::onRejected, this));

        auto winBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
        auto fixed = sfg::Fixed::Create();
        fixed->Put(acceptButton, sf::Vector2f(350.f, 30.f));
        fixed->Put(label, sf::Vector2f(5.0f, 2.0f));
        fixed->Put(rejectButton, sf::Vector2f(230 + 0, 30.0f));

        winBox->Pack(fixed, false, true);
        Add(winBox);
    }

    bool ConfirmationWindow::isRejected() const
    {
        return m_rejected;
    }

    bool ConfirmationWindow::isAccepted() const
    {
        return m_accepted;
    }

    void ConfirmationWindow::onAccepted()
    {
        m_accepted = true;
        m_guiManager.removeTopMost();
    }

    void ConfirmationWindow::onRejected()
    {
        m_rejected = true;
        m_guiManager.removeTopMost();
    }
}
}