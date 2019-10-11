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

#include <functional>
#include <map>
#include <queue>
#include <vector>
#include <memory>

#include "Debug/DebugGameScreen.hpp"
#include "Screens/GameScreen.hpp"

namespace nanowars {
namespace core {
    class Application;
}
namespace debug {

    using namespace core;

    using std::map;
    using std::queue;
    using std::string;
    using std::vector;
    using std::weak_ptr;

    class DebugConsole
    {
    public:
        DebugConsole(Application& app);

        void execute(const string& cmd);

        bool isStreamEmpty() const;
        string popStream();

        void injectDebugScreen();
        void removeDebugScreen();

    private:
        typedef const vector<string>& args_t;

        void cmdDebug(args_t args);
        void cmdCamera(args_t args);
        void cmdExit(args_t args);

        void write(const string&);
        void initCommands();

        GameScreen* getGameScreen();

        DebugGameScreen* m_debugGameScreen;

        map<string, std::function<void(args_t)>> m_commands;
        queue<string> m_stream;
        Application& m_application;
    };
}
}