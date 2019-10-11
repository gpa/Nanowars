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

#include "Assets/AssetPathResolver.hpp"

namespace nanowars {
namespace assets {

    string AssetPathResolver::getPath(TextureAsset textureAsset) const
    {
        const char* files[] = { "landscape1.png", "rockets.png" };
        return "data/textures/" + string(files[(int)textureAsset]);
    }

    string AssetPathResolver::getPath(SoundAsset textureAsset) const
    {
        return "";
    }

    string AssetPathResolver::getPath(SchemaAsset textureAsset) const
    {
        const char* files[] = { "rocket1.json" };
        return "data/schemas/" + string(files[(int)textureAsset]);
    }

    string AssetPathResolver::getPath(FontAsset textureAsset) const
    {
        return "";
    }
}
}