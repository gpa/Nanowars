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
#include "Assets/AssetPathResolver.hpp"
#include "Assets/Assets.hpp"
#include <SFML/Graphics.hpp>
#include <catch2/catch.hpp>
#include <iostream>

using namespace nanowars::assets;
using namespace std;

TEST_CASE("Asset manager reuses and frees assets correctly")
{
    sf::Texture* first = nullptr;
    auto manager = AssetManager(AssetPathResolver());

    {
        AssetContainer container = manager.getNewContainer();
        first = &container.getTexture(TextureAsset_Landscape1);
        sf::Texture* second = &container.getTexture(TextureAsset_Landscape1);
        REQUIRE(first == second);
        manager.clean();
        sf::Texture* third = &container.getTexture(TextureAsset_Landscape1);
        REQUIRE(second == third);
        {
            auto container = manager.getNewContainer();
            sf::Texture* five = &container.getTexture(TextureAsset_Landscape1);
            REQUIRE(five == first);
        }
    }
    manager.clean();
    REQUIRE(manager.isEmpty());
}