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

namespace nanowars {
namespace debug {

    using std::map;
    using std::queue;
    using std::string;
    using std::vector;
    using std::weak_ptr;
    using std::function;

    class DebugManager;

    class DebugConsole
    {
    public:
        typedef const vector<string>& args_t;

        DebugConsole(DebugManager& parent);

        void execute(const string& cmd);
        bool isStreamEmpty() const;
        string popStream();

        void registerCommand(string name, function<void(args_t)> func);

    private:
        void write(const string&);

        map<string, function<void(args_t)>> m_commands;
        queue<string> m_stream;
        DebugManager& m_debugManager;
    };
}
}