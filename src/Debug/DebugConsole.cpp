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

#include "Debug/DebugConsole.hpp"
#include "Debug/DebugManager.hpp"

#include <boost/algorithm/string.hpp>
#include <functional>
#include <sstream>

namespace nanowars {
namespace debug {

    using namespace core;

    DebugConsole::DebugConsole(DebugManager& debugManager)
        : m_debugManager(debugManager)
    {
    }

    void DebugConsole::registerCommand(string name, function<void(args_t)> func)
    {
        m_commands.insert(std::make_pair(name, func));
    }

    bool DebugConsole::isStreamEmpty() const
    {
        return m_stream.size() == 0;
    }

    string DebugConsole::popStream()
    {
        string line = m_stream.front();
        m_stream.pop();
        return line;
    }

    void DebugConsole::write(const string& data)
    {
        m_stream.push(data);
    }

    void DebugConsole::execute(const string& input)
    {
        std::vector<std::string> cmds;
        boost::split(cmds, input, boost::is_any_of(";"));

        for (string cmd : cmds)
        {
            if (cmd.empty())
                return;

            vector<string> args;
            string buf;
            std::stringstream ss(cmd);
            while (ss >> buf)
                args.push_back(buf);

            if (args.size() == 0)
                return;

            auto exec = args[0];
            auto find = m_commands.find(exec);
            if (find == m_commands.end())
                write(exec + ": Command not found");
            else
                find->second(args);
        }
    }
}
}