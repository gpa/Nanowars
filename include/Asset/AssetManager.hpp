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

#include "Asset/AssetHolder.hpp"
#include "Asset/AssetPathResolver.hpp"
#include "Asset/Assets.hpp"

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
namespace asset {

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
        shared_ptr<const TAsset> getAsset(map<TKey, weak_ptr<const TAsset>>* container, TKey identifier);

        template <typename TKey, typename TAsset>
        void clean(map<TKey, weak_ptr<const TAsset>>& container);
    };
}
}