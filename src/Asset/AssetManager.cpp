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

#include "Asset/AssetManager.hpp"

namespace nanowars {
namespace asset {

    template <typename TKey, typename TAsset>
    shared_ptr<const TAsset> AssetManager::getAsset(map<TKey, weak_ptr<const TAsset>>* container, TKey identifier)
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
    void AssetManager::clean(map<TKey, weak_ptr<const TAsset>>& container)
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

    template <typename TAsset, typename TKey>
    shared_ptr<TAsset> AssetManager::load(TKey key) const
    {
        auto asset = std::make_shared<TAsset>();
        string path = m_assetPathResolver.getPath(key);
        asset->loadFromFile(path);
        return asset;
    }

    AssetManager::AssetManager(AssetPathResolver assetPathResolver)
        : m_assetPathResolver(assetPathResolver)
        , m_loadedTextures()
        , m_loadedSchemas()
    {
    }

    AssetHolder AssetManager::getNewHolder()
    {
        return AssetHolder(*this);
    }

    shared_ptr<const Texture> AssetManager::getTexture(TextureAsset textureAsset)
    {
        return getAsset(&m_loadedTextures, textureAsset);
    }

    shared_ptr<const SoundBuffer> AssetManager::getSound(SoundAsset soundAsset)
    {
        return getAsset(&m_loadedSounds, soundAsset);
    }

    shared_ptr<const Document> AssetManager::getSchema(SchemaAsset schemaAsset)
    {
        return getAsset(&m_loadedSchemas, schemaAsset);
    }

    shared_ptr<const Font> AssetManager::getFont(FontAsset fontAsset)
    {
        return getAsset(&m_loadedFonts, fontAsset);
    }

    void AssetManager::clean()
    {
        clean(m_loadedTextures);
        clean(m_loadedSounds);
        clean(m_loadedSchemas);
        clean(m_loadedFonts);
    }

    template shared_ptr<const Texture> AssetManager::getAsset<TextureAsset, Texture>(map<TextureAsset, weak_ptr<const Texture>>* container, TextureAsset identifier);
    template shared_ptr<const SoundBuffer> AssetManager::getAsset<SoundAsset, SoundBuffer>(map<SoundAsset, weak_ptr<const SoundBuffer>>* container, SoundAsset identifier);
    template shared_ptr<const Font> AssetManager::getAsset<FontAsset, Font>(map<FontAsset, weak_ptr<const Font>>* container, FontAsset identifier);
    template shared_ptr<const Document> AssetManager::getAsset<SchemaAsset, Document>(map<SchemaAsset, weak_ptr<const Document>>* container, SchemaAsset identifier);

    template void AssetManager::clean<TextureAsset, Texture>(map<TextureAsset, weak_ptr<const Texture>>& container);
    template void AssetManager::clean<SoundAsset, SoundBuffer>(map<SoundAsset, weak_ptr<const SoundBuffer>>& container);
    template void AssetManager::clean<FontAsset, Font>(map<FontAsset, weak_ptr<const Font>>& container);
    template void AssetManager::clean<SchemaAsset, Document>(map<SchemaAsset, weak_ptr<const Document>>& container);

    template shared_ptr<Texture> AssetManager::load<Texture, TextureAsset>(TextureAsset key) const;
    template shared_ptr<SoundBuffer> AssetManager::load<SoundBuffer, SoundAsset>(SoundAsset key) const;
    template shared_ptr<Font> AssetManager::load<Font, FontAsset>(FontAsset key) const;

    template <>
    shared_ptr<Document> AssetManager::load<Document, SchemaAsset>(SchemaAsset key) const
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