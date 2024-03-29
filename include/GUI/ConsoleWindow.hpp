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

#pragma once

#include "GUI/FixedPositionWindow.hpp"
#include "GUI/GUIManager.hpp"
#include "Debug/DebugConsole.hpp"

namespace nanowars {
namespace gui {

    using namespace debug;

    class ConsoleWindow : public FixedPositionWindow
    {

    public:
        ConsoleWindow(GUIManager& guiManager, AssetHolder&& assetHolder, DebugConsole& debugConsole);


        void onTopMostGained(shared_ptr<Window> previousTopMost) override;
        void HandleEvent(const Event& event) override;

    protected:
        void initialize() override;

    private:
        shared_ptr<sfg::Entry> m_consoleInput;
        shared_ptr<sfg::Label> m_consoleOutput;

        shared_ptr<sfg::ScrolledWindow> m_consoleScrollWindow;
        vector<string> m_inputs;
        int m_inputScrollCurrentIndex;

        DebugConsole& m_console;

        void readConsoleStream();
        void execute();
        void adjustScrollbar();
        void clear();

        // Signals
        void handleConsoleInput();
    };
}
}