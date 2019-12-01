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

namespace nanowars {
namespace gui {

    using namespace sfg;

    ConsoleWindow::ConsoleWindow(GUIManager& guiManager, AssetHolder&& assetHolder, DebugConsole& debugConsole)
        : FixedPositionWindow(guiManager, std::move(assetHolder))
        , m_console(debugConsole)
    {
    }

    void ConsoleWindow::initialize()
    {
        SetStyle(sfg::Window::Style::BACKGROUND);

        auto consoleOutput = sfg::ScrolledWindow::Create();
        consoleOutput->SetScrollbarPolicy(sfg::ScrolledWindow::VERTICAL_AUTOMATIC);
        consoleOutput->SetRequisition(sf::Vector2f(800.f, 200.f));
        consoleOutput->SetPlacement(sfg::ScrolledWindow::Placement::TOP_LEFT);

        auto consoleOutputBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
        consoleOutputBox->SetOrientation(sfg::Box::Orientation::VERTICAL);
        consoleOutput->AddWithViewport(consoleOutputBox);

        auto consoleBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);

        auto consoleInput = sfg::Entry::Create();
        consoleInput->SetRequisition(sf::Vector2f(80.f, 0.f));
        consoleInput->SetText(">");

        auto consoleLabel = sfg::Label::Create("");
        consoleOutputBox->Pack(consoleLabel);

        consoleInput->GetSignal(sfg::Entry::OnTextChanged).Connect(std::bind(&ConsoleWindow::handleConsoleInput, this));

        consoleBox->Pack(consoleOutput, true, true);
        consoleBox->Pack(consoleInput);

        Add(consoleBox);

        m_consoleInput = consoleInput;
        m_consoleOutput = consoleLabel;
        m_consoleScrollWindow = consoleOutput;
        SetRequisition(sf::Vector2f(static_cast<float>(m_guiManager.getWindow().getSize().x), 200.f));
        FixedPositionWindow::initialize();
    }

    void ConsoleWindow::onTopMostGained(shared_ptr<Window> previousTopMost)
    {
        FixedPositionWindow::onTopMostGained(previousTopMost);
        m_consoleInput->GrabFocus();
        m_consoleInput->SetCursorPosition(1);
    }

    void ConsoleWindow::HandleEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::TextEntered && event.text.unicode == '`')
            return;

        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Key::Tilde)
        {
            m_guiManager.removeTopMost();
            return;
        }

        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Key::Return)
            execute();

        Window::HandleEvent(event);
    }

    void ConsoleWindow::execute()
    {
        std::string cmd = m_consoleInput->GetText();
        auto input = cmd.substr(1, cmd.size());

        if (input == "" || input == " ")
            return;

        if (input == "clear")
        {
            clear();
            return;
        }

        m_console.execute(input);

        m_inputs.push_back(input);
        m_inputScrollCurrentIndex = static_cast<int>(m_inputs.size());

        const string& output = m_consoleOutput->GetText();
        m_consoleOutput->SetText(output + "\n" + cmd);

        if (m_console.isStreamEmpty())
            adjustScrollbar();

        m_consoleInput->SetText(">");
        m_consoleInput->SetCursorPosition(1);
        readConsoleStream();
    }

    void ConsoleWindow::clear()
    {
        m_consoleOutput->SetText(">clear");
        m_consoleInput->SetText(">");
        m_consoleInput->SetCursorPosition(1);
    }

    void ConsoleWindow::handleConsoleInput()
    {
        string input = m_consoleInput->GetText();
        if (input.empty() || input[0] != '>')
        {
            m_consoleInput->SetText(">" + input);
            m_consoleInput->SetCursorPosition(1);
        }
    }

    void ConsoleWindow::adjustScrollbar()
    {
        m_consoleScrollWindow->GetVerticalAdjustment()->SetValue(m_consoleScrollWindow->GetVerticalAdjustment()->GetUpper() + 10);
    }

    void ConsoleWindow::readConsoleStream()
    {
        bool updated = false;
        while (!m_console.isStreamEmpty())
        {
            string line = m_console.popStream();

            const string& output = m_consoleOutput->GetText();
            auto l = output != "" ? output + "\n" + line : line;
            m_consoleOutput->SetText(l);
            updated = true;
        }

        if (updated)
            adjustScrollbar();
    }
}
}