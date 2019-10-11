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

#include "Config/PersistentConfigManager.hpp"

#include <boost/assert.hpp>
#include <boost/filesystem/fstream.hpp>
#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <sstream>

namespace nanowars {
namespace config {
    using namespace rapidjson;
    using namespace boost::filesystem;

    PersistentConfigManager::PersistentConfigManager(std::string configFile)
        : m_configFile(configFile)
    {
    }

    void PersistentConfigManager::load()
    {
        if (!exists(m_configFile))
        {
            save();
            return;
        }

        std::ifstream file(m_configFile);
        if (!file.is_open())
            throw new std::invalid_argument("Failed to open the file");

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string data = buffer.str();

        Document schema;
        if (schema.Parse(data.c_str()).HasParseError())
            throw new std::runtime_error("The JSON Format of the file is invalid");

        parseJson(schema);
    }

    void PersistentConfigManager::save()
    {
        StringBuffer s = generateJson();
        std::ofstream ofs(m_configFile);
        ofs << s.GetString();
        ofs.close();
    }

    void PersistentConfigManager::parseJson(const Document& document)
    {
        for (auto it = document.MemberBegin(); it != document.MemberEnd(); ++it)
        {
            string name = it->name.GetString();
            auto find = m_entries.find(name);

            if (find == m_entries.end())
                throw new std::invalid_argument("The config key " + name + " is unknown.");

            int type = m_entries[name].value.which();
            switch (type)
            {
            case 0:
                if (!it->value.IsBool())
                    continue;
                m_entries[name].value = it->value.GetBool();
                break;
            case 1:
                if (!it->value.IsInt())
                    continue;
                m_entries[name].value = it->value.GetInt();
                break;
            case 2:
                if (!it->value.IsFloat())
                    continue;
                m_entries[name].value = it->value.GetFloat();
                break;
            case 3:
                if (!it->value.IsString())
                    continue;
                m_entries[name].value = string(it->value.GetString());
                break;
            default:
                break;
            }
        }
    }

    StringBuffer PersistentConfigManager::generateJson()
    {
        StringBuffer stringBuffer;
        PrettyWriter<StringBuffer> writer(stringBuffer);

        writer.StartObject();

        for (const auto& entry : m_entries)
        {
            int type = entry.second.value.which();
            BOOST_ASSERT(type >= 0 && type <= 3);

            writer.Key(entry.first.c_str());

            if (type == 0)
                writer.Bool(getBool(entry.first));
            else if (type == 1)
                writer.Int(getInt(entry.first));
            else if (type == 2)
                writer.Double(getFloat(entry.first));
            else if (type == 3)
                writer.String(getString(entry.first).c_str());
        }

        writer.EndObject();
        return stringBuffer;
    }
}
}