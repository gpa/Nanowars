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

    ConsoleWindow::ConsoleWindow(GUIManager& guiManager, AssetHolder&& assetHolder, DebugConsole& debugConsole)
        : Window(guiManager, std::move(assetHolder))
        , m_console(debugConsole)
    {
        m_window->SetStyle(sfg::Window::Style::BACKGROUND);

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

        m_window->Add(consoleBox);

        m_consoleInput = consoleInput;
        m_consoleOutput = consoleLabel;
        m_consoleScrollWindow = consoleOutput;
        m_window->Show(false);
        m_isVisible = false;
    }

    void ConsoleWindow::update(float dt)
    {
        m_window->SetRequisition(sf::Vector2f(m_guiManager.getApplication().getWindow().getSize().x, 200.f));
        readConsoleStream();
        Window::update(dt);
    }

    void ConsoleWindow::handleEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::TextEntered && event.text.unicode == '`')
            return;

        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Key::Tilde)
        {
            m_isVisible = !m_isVisible;
            m_window->Show(m_isVisible);

            if (m_isVisible)
                m_consoleInput->GrabFocus();

            return;
        }

        if (m_consoleInput->GetCursorPosition() == 0)
            m_consoleInput->SetCursorPosition(1);

        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Key::Return && m_isVisible)
            execute();

        Window::handleEvent(event);
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
        m_inputScrollCurrentIndex = m_inputs.size();

        const string& output = m_consoleOutput->GetText();
        m_consoleOutput->SetText(output + "\n" + cmd);

        if (m_console.isStreamEmpty())
            adjustScrollbar();

        m_consoleInput->SetText(">");
        m_consoleInput->SetCursorPosition(1);
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