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

#include "Config/ConfigEntry.hpp"
#include "Config/ConfigManager.hpp"

namespace nanowars {
namespace config {
    namespace userConfiguration {
        using Entry = ConfigEntry::configEntry_t;

        namespace general {
            constexpr auto language = "general.language";
        }
        namespace graphics {
            constexpr auto resolution = "graphics.resolution";
            constexpr auto antiAliasing = "graphics.anti-aliasing";
            constexpr auto vsync = "graphics.vsync";
            constexpr auto fullscreen = "graphics.fullscreen";
            constexpr auto showFps = "graphics.show-fps";
        }
        namespace audio {
            constexpr auto menuEffects = "audio.menu-effects";
            constexpr auto menuMusic = "audio.menu-music";
            constexpr auto gameEffects = "audio.game-effects";
            constexpr auto gameMusic = "audio.game-music";
        }
        namespace controls {
            constexpr auto mainThrust = "controls.main.thrust";
            constexpr auto mainLeft = "controls.main.left";
            constexpr auto mainRight = "controls.main.right";
            constexpr auto mainShoot = "controls.main.shoot";
            constexpr auto mainChat = "controls.main.chat";

            constexpr auto altThrust = "controls.alt.thrust";
            constexpr auto altLeft = "controls.alt.left";
            constexpr auto altRight = "controls.alt.right";
            constexpr auto altShoot = "controls.alt.shoot";
            constexpr auto altChat = "controls.alt.chat";
        }
        namespace network {
            constexpr auto name = "network.name";
        }

        inline void populateWithDefaultValues(ConfigManager& configManager)
        {
            auto& cm = configManager;
            cm.setEntry(ConfigEntry(general::language, Entry(string("english"))));

            cm.setEntry(ConfigEntry(graphics::resolution, Entry(string("1024x768@32"))));
            cm.setEntry(ConfigEntry(graphics::antiAliasing, Entry(8)));
            cm.setEntry(ConfigEntry(graphics::vsync, Entry(true)));
            cm.setEntry(ConfigEntry(graphics::fullscreen, Entry(false)));
            cm.setEntry(ConfigEntry(graphics::showFps, Entry(false)));

            cm.setEntry(ConfigEntry(audio::gameEffects, Entry(100.0f)));
            cm.setEntry(ConfigEntry(audio::gameMusic, Entry(100.0f)));
            cm.setEntry(ConfigEntry(audio::menuEffects, Entry(100.0f)));
            cm.setEntry(ConfigEntry(audio::menuMusic, Entry(100.0f)));

            cm.setEntry(ConfigEntry(controls::mainThrust, Entry(string("Up"))));
            cm.setEntry(ConfigEntry(controls::mainLeft, Entry(string("Right"))));
            cm.setEntry(ConfigEntry(controls::mainRight, Entry(string("Left"))));
            cm.setEntry(ConfigEntry(controls::mainShoot, Entry(string("Space"))));
            cm.setEntry(ConfigEntry(controls::mainChat, Entry(string("Enter"))));

            cm.setEntry(ConfigEntry(controls::altThrust, Entry(string("W"))));
            cm.setEntry(ConfigEntry(controls::altLeft, Entry(string("D"))));
            cm.setEntry(ConfigEntry(controls::altRight, Entry(string("A"))));
            cm.setEntry(ConfigEntry(controls::altShoot, Entry(string("RControl"))));
            cm.setEntry(ConfigEntry(controls::altChat, Entry(string("T"))));

            cm.setEntry(ConfigEntry(network::name, Entry(string("Unnamed"))));
        }
    }
}
}