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
#include "Screens/GameScreen.hpp"
#include "Screens/Screen.hpp"
#include "Core/Application.hpp"

#include <boost/algorithm/string.hpp>
#include <functional>
#include <sstream>

namespace nanowars {
namespace debug {

    using namespace screens;
    using namespace graphics;
    using namespace core;

    DebugConsole::DebugConsole(Application& app)
        : m_application(app)
    {
        initCommands();
    }

    void DebugConsole::initCommands()
    {
        m_debugGameScreen = nullptr;
        m_commands.insert(std::make_pair("exit", std::bind(&DebugConsole::cmdExit, this, std::placeholders::_1)));
        m_commands.insert(std::make_pair("quit", std::bind(&DebugConsole::cmdExit, this, std::placeholders::_1)));
        m_commands.insert(std::make_pair("camera", std::bind(&DebugConsole::cmdCamera, this, std::placeholders::_1)));
        m_commands.insert(std::make_pair("debug", std::bind(&DebugConsole::cmdDebug, this, std::placeholders::_1)));
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

    void DebugConsole::cmdExit(args_t args)
    {
        m_application.m_window.close();
    }

    void DebugConsole::cmdCamera(args_t args)
    {
        if (m_debugGameScreen == nullptr)
            injectDebugScreen();

        if (m_debugGameScreen != nullptr)
        {
            auto* gameScreen = getGameScreen();
            if (m_debugGameScreen->getFreeCameraEnabled())
            {
                m_debugGameScreen->setFreeCameraEnabled(false);
                gameScreen->m_activeCamera = &gameScreen->m_followingCamera;
            }
            else
            {
                gameScreen->m_activeCamera = &m_debugGameScreen->getFreeCamera();
                m_debugGameScreen->setFreeCameraEnabled(true);
            }
        }
    }

    void DebugConsole::cmdDebug(args_t args)
    {
        uint32 flags = 0;

        if (m_debugGameScreen == nullptr)
            injectDebugScreen();

        if (args.size() == 1)
        {
            if (m_debugGameScreen->getDebugViewEnabled())
            {
                m_debugGameScreen->setDebugViewEnabled(false);
            }
            else
            {
                flags = b2Draw::e_shapeBit | b2Draw::e_particleBit;
                m_debugGameScreen->setDebugViewEnabled(true);
            }
        }

        for (int i = 1; i < args.size(); ++i)
        {
            auto arg = args[i];
            if (arg == "aabb")
                flags = !(flags & b2Draw::e_aabbBit) ? flags | b2Draw::e_aabbBit : flags & ~b2Draw::e_aabbBit;
            else if (arg == "mass")
                flags = !(flags & b2Draw::e_centerOfMassBit) ? flags | b2Draw::e_centerOfMassBit : flags & ~b2Draw::e_centerOfMassBit;
            else if (arg == "joint")
                flags = !(flags & b2Draw::e_jointBit) ? flags | b2Draw::e_jointBit : flags & ~b2Draw::e_jointBit;
            else if (arg == "pair")
                flags = !(flags & b2Draw::e_pairBit) ? flags | b2Draw::e_pairBit : flags & ~b2Draw::e_pairBit;
            else if (arg == "particle")
                flags = !(flags & b2Draw::e_particleBit) ? flags | b2Draw::e_particleBit : flags & ~b2Draw::e_particleBit;
            else if (arg == "shape")
                flags = !(flags & b2Draw::e_shapeBit) ? flags | b2Draw::e_shapeBit : flags & ~b2Draw::e_shapeBit;
            else
            {
                write("Invalid arguments");
                return;
            }
        }

        if (flags == 0)
        {
            m_debugGameScreen->setDebugViewEnabled(false);
        }
        else
        {
            m_debugGameScreen->SetFlags(flags);
        }
    }

    GameScreen* DebugConsole::getGameScreen()
    {
        static_assert(std::is_polymorphic<Screen>::value, "This should be polymorphic.");
        b2World* world = nullptr;
        for (int i = 0; i < m_application.m_screens.size(); ++i)
        {
            Screen* screen = m_application.m_screens[i].get();
            if (typeid(*screen) == typeid(GameScreen))
            {
                GameScreen* gameScreen = reinterpret_cast<GameScreen*>(screen);
                return gameScreen;
            }
        }

        return nullptr;
    }

    void DebugConsole::injectDebugScreen()
    {
        GameScreen* gameScreen = getGameScreen();
        b2World* world = nullptr;
        if (gameScreen != nullptr)
            world = &gameScreen->m_gameWorld.m_world;

        if (world != nullptr)
        {
            m_application.m_screens.push_back(std::make_unique<DebugGameScreen>(*world));
            m_debugGameScreen = static_cast<DebugGameScreen*>(m_application.m_screens.back().get());
        }
    }

    void DebugConsole::removeDebugScreen()
    {
        for (int i = 0; i < m_application.m_screens.size(); ++i)
        {
            if (m_application.m_screens[i].get() == m_debugGameScreen)
            {
                m_application.m_screens.erase(m_application.m_screens.begin() + i);
                m_debugGameScreen = nullptr;
                break;
            }
        }
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