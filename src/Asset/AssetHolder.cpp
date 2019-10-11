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

#include "Asset/AssetHolder.hpp"
#include "Asset/AssetManager.hpp"

namespace nanowars {
namespace asset {
    AssetHolder::AssetHolder(AssetManager& assetManager)
        : m_assetManager(assetManager)
    {
    }

    AssetHolder AssetHolder::getNewHolder()
    {
        return m_assetManager.getNewHolder();
    }

    const Texture& AssetHolder::getTexture(TextureAsset textureAsset)
    {
        shared_ptr<const Texture> texture = m_assetManager.getTexture(textureAsset);
        holdAsset(texture, ((assetEntryId_t)(int)textureAsset));
        return *(texture.get());
    }

    const SoundBuffer& AssetHolder::getSound(SoundAsset soundAsset)
    {
        shared_ptr<const SoundBuffer> sound = m_assetManager.getSound(soundAsset);
        holdAsset(sound, (assetEntryId_t)(1000 + (int)soundAsset));
        return *(sound.get());
    }

    const Document& AssetHolder::getSchema(SchemaAsset schemaAsset)
    {
        shared_ptr<const Document> schema = m_assetManager.getSchema(schemaAsset);
        holdAsset(schema, (assetEntryId_t)(2000 + (int)schemaAsset));
        return *(schema.get());
    }

    const Font& AssetHolder::getFont(FontAsset fontAsset)
    {
        shared_ptr<const Font> font = m_assetManager.getFont(fontAsset);
        holdAsset(font, (assetEntryId_t)(3000 + (int)fontAsset));
        return *(font.get());
    }

    Texture& AssetHolder::getUniqueTexture(TextureAsset textureAsset)
    {
        auto texture = m_assetManager.load<Texture, TextureAsset>(textureAsset);
        m_loadedAssets.push_back(assetEntry_t(texture));
        return *(texture.get());
    }

    SoundBuffer& AssetHolder::getUniqueSound(SoundAsset soundAsset)
    {
        auto sound = m_assetManager.load<SoundBuffer, SoundAsset>(soundAsset);
        m_loadedAssets.push_back(assetEntry_t(sound));
        return *(sound.get());
    }

    Document& AssetHolder::getUniqueSchema(SchemaAsset schemaAsset)
    {
        auto schema = m_assetManager.load<Document, SchemaAsset>(schemaAsset);
        m_loadedAssets.push_back(assetEntry_t(schema));
        return *(schema.get());
    }

    Font& AssetHolder::getUniqueFont(FontAsset fontAsset)
    {
        auto font = m_assetManager.load<Font, FontAsset>(fontAsset);
        m_loadedAssets.push_back(assetEntry_t(font));
        return *(font.get());
    }
}
}