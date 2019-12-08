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

namespace nanowars {
namespace config {

    using Entry = ConfigEntry::configEntry_t;

    ConfigEntry& ConfigManager::getEntry(const string& name)
    {
        return m_entries[name];
    }

    void ConfigManager::setEntry(const ConfigEntry& entry)
    {
        m_entries[entry.name] = entry;
    }

    void ConfigManager::resetEntry(string entryId)
    {
        m_entries[entryId].value = m_entries[entryId].defaultValue;
    }

    bool ConfigManager::getBool(string entryId) const
    {
        return boost::get<bool>(m_entries[entryId].value);
    }

    int ConfigManager::getInt(string entryId) const
    {
        return boost::get<int>(m_entries[entryId].value);
    }

    float ConfigManager::getFloat(string entryId) const
    {
        return boost::get<float>(m_entries[entryId].value);
    }

    string ConfigManager::getString(string entryId) const
    {
        return boost::get<string>(m_entries[entryId].value);
    }
}
}