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

#include "Assets/AssetManager.hpp"

namespace nanowars {
namespace assets {

    AssetManager::AssetManager(AssetPathResolver assetPathResolver)
        : m_assetPathResolver(assetPathResolver)
        , m_loadedTextures()
        , m_loadedSchemas()
    {
    }

    AssetContainer AssetManager::getNewContainer()
    {
        return AssetContainer(*this);
    }

    shared_ptr<Texture> AssetManager::getTexture(TextureAsset textureAsset)
    {
        return getAsset(&m_loadedTextures, textureAsset);
    }

    shared_ptr<Image> AssetManager::getImage(TextureAsset textureAsset)
    {
        return getAsset(&m_loadedImages, textureAsset);
    }

    shared_ptr<SoundBuffer> AssetManager::getSound(SoundAsset soundAsset)
    {
        return getAsset(&m_loadedSounds, soundAsset);
    }

    shared_ptr<Document> AssetManager::getSchema(SchemaAsset schemaAsset)
    {
        return getAsset(&m_loadedSchemas, schemaAsset);
    }

    shared_ptr<Font> AssetManager::getFont(FontAsset fontAsset)
    {
        return getAsset(&m_loadedFonts, fontAsset);
    }

    void AssetManager::clean()
    {
        clean(m_loadedTextures);
        clean(m_loadedImages);
        clean(m_loadedSounds);
        clean(m_loadedSchemas);
        clean(m_loadedFonts);
    }

    bool AssetManager::isEmpty()
    {
        return m_loadedTextures.size() == 0 && m_loadedImages.size() == 0
            && m_loadedSounds.size() == 0 && m_loadedSchemas.size() == 0 && m_loadedFonts.size() == 0;
    }
}
}