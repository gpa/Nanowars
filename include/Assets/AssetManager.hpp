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

#include "Assets/AssetContainer.hpp"
#include "Assets/AssetPathResolver.hpp"
#include "Assets/Assets.hpp"

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Font.hpp>
#include <rapidjson/document.h>

#include <fstream>
#include <map>
#include <memory>
#include <sstream>

namespace nanowars {
namespace assets {

    using rapidjson::Document;
    using std::map;
    using std::shared_ptr;
    using std::weak_ptr;
    using namespace sf;

    class AssetManager
    {
    public:
        AssetManager(AssetPathResolver assetPathResolver);

        AssetContainer getNewContainer();

        void clean();
        bool isEmpty();

        shared_ptr<Texture> getTexture(TextureAsset textureAsset);
        shared_ptr<Image> getImage(TextureAsset textureAsset);
        shared_ptr<SoundBuffer> getSound(SoundAsset textureAsset);
        shared_ptr<Document> getSchema(SchemaAsset textureAsset);
        shared_ptr<Font> getFont(FontAsset textureAsset);

    public:
        map<TextureAsset, weak_ptr<Texture>> m_loadedTextures;
        map<TextureAsset, weak_ptr<Image>> m_loadedImages;
        map<SoundAsset, weak_ptr<SoundBuffer>> m_loadedSounds;
        map<FontAsset, weak_ptr<Font>> m_loadedFonts;
        map<SchemaAsset, weak_ptr<Document>> m_loadedSchemas;
        AssetPathResolver m_assetPathResolver;

        template <typename TKey, typename TAsset>
        shared_ptr<TAsset> getAsset(map<TKey, weak_ptr<TAsset>>* container, TKey identifier)
        {
            auto iter = container->find(identifier);
            if (iter != container->end())
            {
                weak_ptr<TAsset> weakReference = (*iter).second;
                if (!weakReference.expired())
                {
                    shared_ptr<TAsset> Asset = weakReference.lock();
                    return Asset;
                }
            }

            shared_ptr<TAsset> Asset = loadFromFile<TKey, TAsset>(identifier);
            (*container)[identifier] = Asset;
            return Asset;
        }

        template <typename TKey, typename TAsset>
        void clean(map<TKey, weak_ptr<TAsset>>& container)
        {
            auto iter = container.begin();
            for (; iter != container.end();)
            {
                if (iter->second.expired())
                    container.erase(iter++);
                else
                    ++iter;
            }
        }

        template <typename TKey, typename TAsset>
        shared_ptr<TAsset> loadFromFile(TKey key)
        {
            auto Asset = std::make_shared<TAsset>();
            string path = m_assetPathResolver.getPath(key);
            Asset->loadFromFile(path);
            return Asset;
        }
    };

    template <>
    inline shared_ptr<Document> AssetManager::loadFromFile<SchemaAsset, Document>(SchemaAsset key)
    {
        string path = m_assetPathResolver.getPath(key);
        std::ifstream file(path);
        if (!file.is_open())
            throw new std::invalid_argument("Failed to open file " + path);

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string data = buffer.str();

        auto Asset = std::make_shared<Document>();
        if (Asset->Parse(data.c_str()).HasParseError())
            throw new std::runtime_error("Failed to parse " + path);
        return Asset;
    }
}
}