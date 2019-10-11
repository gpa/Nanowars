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

#include "Assets/AssetContainer.hpp"
#include "Assets/AssetManager.hpp"

namespace nanowars {
namespace assets {
    AssetContainer::AssetContainer(AssetManager& assetManager)
        : m_assetManager(assetManager)
    {
    }

    AssetContainer AssetContainer::getNewContainer()
    {
        return m_assetManager.getNewContainer();
    }

    Texture& AssetContainer::getTexture(TextureAsset textureAsset)
    {
        shared_ptr<Texture> texture = m_assetManager.getTexture(textureAsset);
        m_loadedTextures[textureAsset] = texture;
        return *(texture.get());
    }

    Image& AssetContainer::getImage(TextureAsset textureAsset)
    {
        shared_ptr<Image> image = m_assetManager.getImage(textureAsset);
        m_loadedImages[textureAsset] = image;
        return *(image.get());
    }

    SoundBuffer& AssetContainer::getSound(SoundAsset soundAsset)
    {
        shared_ptr<SoundBuffer> sound = m_assetManager.getSound(soundAsset);
        m_loadedSounds[soundAsset] = sound;
        return *(sound.get());
    }

    Document& AssetContainer::getSchema(SchemaAsset schemaAsset)
    {
        shared_ptr<Document> schema = m_assetManager.getSchema(schemaAsset);
        m_loadedSchemas[schemaAsset] = schema;
        return *(schema.get());
    }

    Font& AssetContainer::getFont(FontAsset fontAsset)
    {
        shared_ptr<Font> font = m_assetManager.getFont(fontAsset);
        m_loadedFonts[fontAsset] = font;
        return *(font.get());
    }
}
}