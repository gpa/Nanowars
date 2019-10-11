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

#include "Config/ConfigManager.hpp"
#include <SFML/Graphics.hpp>
#include <catch2/catch.hpp>

using namespace nanowars::config;
using namespace std;

using Entry = ConfigEntry::configEntry_t;

TEST_CASE("Config manager stores and retrieves simple data correctly")
{
    ConfigManager configManager;
    configManager.setEntry(ConfigEntry("testEntry", Entry(string("12"))));
    REQUIRE(configManager.getString("testEntry") == "12");
    REQUIRE_THROWS(configManager.getString("xxx"));
    REQUIRE_THROWS(configManager.getInt("testEntry"));
}