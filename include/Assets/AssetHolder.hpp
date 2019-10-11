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

#include "Assets/Assets.hpp"

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Font.hpp>
#include <rapidjson/document.h>

#include <set>
#include <vector>
#include <memory>
#include <boost/variant.hpp>

namespace nanowars {
namespace assets {

    using std::vector;
    using std::set;
    using std::shared_ptr;
    using rapidjson::Document;
    using sf::Image;
    using sf::Texture;
    using sf::SoundBuffer;
    using sf::Font;

    class AssetManager;

    class AssetHolder
    {
    public:
        AssetHolder(AssetManager& assetManager);
        AssetHolder getNewHolder();

        const Texture& getTexture(TextureAsset textureAsset);
        const SoundBuffer& getSound(SoundAsset soundAsset);
        const Document& getSchema(SchemaAsset schemaAsset);
        const Font& getFont(FontAsset fontAsset);

        Texture& getUniqueTexture(TextureAsset textureAsset);
        SoundBuffer& getUniqueSound(SoundAsset soundAsset);
        Document& getUniqueSchema(SchemaAsset schemaAsset);
        Font& getUniqueFont(FontAsset fontAsset);

        template <typename T>
        void holdCustomUntracked(shared_ptr<T> texture);

    private:
        typedef int assetEntryId_t;
        typedef boost::variant<
            shared_ptr<const Texture>,
            shared_ptr<const SoundBuffer>,
            shared_ptr<const Document>,
            shared_ptr<const Font>>
            assetEntry_t;

        vector<assetEntry_t> m_loadedAssets;
        set<assetEntryId_t> m_loadedAssetIds;
        AssetManager& m_assetManager;

        template <typename T>
        void holdAsset(T asset, assetEntryId_t id);
    };

    template <typename T>
    inline void AssetHolder::holdAsset(T asset, assetEntryId_t assetEntryId)
    {
        auto iter = m_loadedAssetIds.find(assetEntryId);
        if (iter == m_loadedAssetIds.end())
        {
            m_loadedAssets.push_back(assetEntry_t(asset));
            m_loadedAssetIds.insert(assetEntryId);
        }
    }

    template <typename T>
    inline void AssetHolder::holdCustomUntracked(shared_ptr<T> asset)
    {
        m_loadedAssets.push_back((assetEntry_t)std::const_pointer_cast<const T>(asset));
    }
}
}