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

#include <map>
#include <memory>

namespace nanowars {
namespace assets {

    using std::map;
    using std::shared_ptr;
    using rapidjson::Document;
    using sf::Image;
    using sf::Texture;
    using sf::SoundBuffer;
    using sf::Font;

    class AssetManager;

    class AssetContainer
    {
    public:
        AssetContainer(AssetManager& assetManager);

        AssetContainer getNewContainer();

        Texture& getTexture(TextureAsset textureAsset);
        Image& getImage(TextureAsset textureAsset);
        SoundBuffer& getSound(SoundAsset textureAsset);
        Document& getSchema(SchemaAsset textureAsset);
        Font& getFont(FontAsset textureAsset);

    private:
        AssetManager& m_assetManager;

        map<TextureAsset, shared_ptr<Texture>> m_loadedTextures;
        map<TextureAsset, shared_ptr<Image>> m_loadedImages;
        map<SoundAsset, shared_ptr<SoundBuffer>> m_loadedSounds;
        map<FontAsset, shared_ptr<Font>> m_loadedFonts;
        map<SchemaAsset, shared_ptr<Document>> m_loadedSchemas;
    };
}
}