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
#include <filesystem>
#include <fstream>
#include <sstream>
#include <boost/algorithm/string.hpp>

namespace nanowars {
namespace globalization {

    TranslationManager::TranslationManager(AssetPathResolver assetPathResolver, std::string language)
    {
        load(assetPathResolver, language);
    }

    void TranslationManager::load(AssetPathResolver assetPathResolver, std::string language)
    {
        m_translationStrings.resize(static_cast<int>(StringTranslation::_StringTranslationCount));
        auto localeFile = std::filesystem::path(assetPathResolver.getLocaleDirectoryLocation()) / std::filesystem::path(language + string(".txt"));

        std::ifstream fileStream(localeFile.c_str());
        if (!fileStream.is_open())
            throw new std::invalid_argument("Failed to open the localization file " + localeFile.string());

        std::string line;
        while (std::getline(fileStream, line, '\n'))
        {
            boost::algorithm::trim_right_if(line, [](char x) { return x == '\r'; });

            int i = 0;
            for (; i < line.size(); ++i)
            {
                if (!(line[i] >= '0' && line[i] <= '9'))
                    break;
            }

            if (i > 0 && line[i] == ' ')
            {
                int translationId = std::stoi(line.substr(0, i));
                std::string translation = line.substr(i + 1, line.size());
                m_translationStrings[translationId] = sf::String(translation);
            }
        }

        fileStream.close();
    }

    TranslationManager::WideString TranslationManager::getTranslation(StringTranslation translation) const
    {
        return m_translationStrings[static_cast<int>(translation)];
    }

    const LanguageConfiguration& TranslationManager::getConfiguration() const
    {
        return m_languageConfiguration;
    }
}
}