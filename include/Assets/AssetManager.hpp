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

#include "Assets/AssetHolder.hpp"
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

        AssetHolder getNewHolder();

        template <typename TAsset, typename TKey>
        shared_ptr<TAsset> load(TKey key) const;

        void clean();
        bool isEmpty();

        shared_ptr<const Texture> getTexture(TextureAsset textureAsset);
        shared_ptr<const SoundBuffer> getSound(SoundAsset textureAsset);
        shared_ptr<const Document> getSchema(SchemaAsset textureAsset);
        shared_ptr<const Font> getFont(FontAsset textureAsset);

    private:
        map<TextureAsset, weak_ptr<const Texture>> m_loadedTextures;
        map<SoundAsset, weak_ptr<const SoundBuffer>> m_loadedSounds;
        map<FontAsset, weak_ptr<const Font>> m_loadedFonts;
        map<SchemaAsset, weak_ptr<const Document>> m_loadedSchemas;
        AssetPathResolver m_assetPathResolver;

        template <typename TKey, typename TAsset>
        shared_ptr<const TAsset> getAsset(map<TKey, weak_ptr<const TAsset>>* container, TKey identifier)
        {
            auto iter = container->find(identifier);
            if (iter != container->end())
            {
                weak_ptr<const TAsset> weakReference = (*iter).second;
                if (!weakReference.expired())
                {
                    shared_ptr<const TAsset> asset = weakReference.lock();
                    return asset;
                }
            }

            shared_ptr<const TAsset> asset = load<TAsset, TKey>(identifier);
            (*container)[identifier] = asset;
            return asset;
        }

        template <typename TKey, typename TAsset>
        void clean(map<TKey, weak_ptr<const TAsset>>& container)
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
    };

    template <typename TAsset, typename TKey>
    shared_ptr<TAsset> AssetManager::load(TKey key) const
    {
        auto asset = std::make_shared<TAsset>();
        string path = m_assetPathResolver.getPath(key);
        asset->loadFromFile(path);
        return asset;
    }

    template <>
    inline shared_ptr<Document> AssetManager::load<Document, SchemaAsset>(SchemaAsset key) const
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