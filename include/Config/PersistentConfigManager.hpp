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

#include "Config/ConfigManager.hpp"

#include <boost/filesystem.hpp>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <string>

namespace nanowars {
namespace config {

    using rapidjson::Document;
    using rapidjson::StringBuffer;
    using std::string;

    class PersistentConfigManager : public ConfigManager
    {
    public:
        PersistentConfigManager(string configfile);

        void load();
        void save();

    private:
        void parseJson(const Document& document);
        StringBuffer generateJson();

        string m_configFile;
    };
}
}