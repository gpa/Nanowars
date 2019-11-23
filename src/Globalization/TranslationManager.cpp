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

#include "Globalization/TranslationManager.hpp"

namespace nanowars {
namespace globalization {
    std::string TranslationManager::getTranslation(StringTranslation translation) const
    {
        // obviously @TODO
        const char* strings[] = {
            "Online Game",
            "LAN Game",
            "Local Game",
            "Settings",
            "Quit Nanowars",
            "Resume",
            "Return to Main Menu",
            "NANOWARS Settings",
            "Graphics",
            "Audio",
            "Controls",
            "Network",
            "Apply changes",
            "Restore defaults",
            "Screen resolution",
            "Fullscreen",
            "V-Sync",
            "Anti-Aliasing",
            "Show FPS",
            "Menu Sound Effects",
            "Game Sound Effects",
            "Menu Music",
            "Game Music",
            "Main",
            "Alternative",
            "Thrust",
            "Left",
            "Right",
            "Shoot",
            "Chat",
            "Network name",
            "<<PRESS>>",
            "Do you want to reset all settings to default values?",
            "Cancel",
            "Do you want to apply made changes?",
            "Discard changes",
            "Unsaved changes"
        };
        return string(strings[(int)translation]);
    }
}
}