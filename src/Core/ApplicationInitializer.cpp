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

#include "Core/ApplicationInitializer.hpp"
#include "Core/Constants.hpp"
#include "Config/UserConfiguration.hpp"

#include <boost/algorithm/string.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

#include <memory>
#include <vector>

namespace nanowars {
namespace core {

    using std::vector;
    using namespace nanowars::config;
    using namespace sf;

    void ApplicationInitializer::initWindow(RenderWindow& window, ConfigManager& configManager)
    {
        bool fullscreen = configManager.getBool(userConfiguration::graphics::fullscreen);
        string resolutionString = configManager.getString(userConfiguration::graphics::resolution);
        int antiAliasing = configManager.getInt(userConfiguration::graphics::antiAliasing);
        bool vsync = configManager.getBool(userConfiguration::graphics::vsync);

        vector<std::string> parsedResolution;
        boost::split(parsedResolution, resolutionString, boost::is_any_of("x"));
        int width = std::stoi(parsedResolution[0].c_str());
        int height = std::stoi(parsedResolution[1].c_str());

        Uint32 style = Style::Default;
        VideoMode videoMode;
        if (fullscreen)
        {
            videoMode = sf::VideoMode::getFullscreenModes()[0];
            style = sf::Style::Fullscreen;
        }
        else
            videoMode = sf::VideoMode(width, height);

        auto windowTitle = constants::windowTitle;

        window.create(videoMode, windowTitle, style, ContextSettings(0, 0, antiAliasing, 1, 1));
        window.setVerticalSyncEnabled(vsync);
    }
}
}