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

#include "Asset/Assets.hpp"
#include <string>

namespace nanowars {
namespace asset {

    using std::string;
    class AssetPathResolver
    {
    public:
        virtual string getPath(TextureAsset textureAsset) const;
        virtual string getPath(SoundAsset textureAsset) const;
        virtual string getPath(SchemaAsset textureAsset) const;
        virtual string getPath(FontAsset textureAsset) const;

        virtual string getDataDirectoryLocation() const;
        virtual string getLocaleDirectoryLocation() const;
    };
}
}