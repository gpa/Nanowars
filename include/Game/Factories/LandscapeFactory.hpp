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
#include "Game/Factories/GameObjectFactory.hpp"
#include "Game/GameObjects/Landscape.hpp"
#include "Game/GameWorld.hpp"

namespace nanowars {
namespace game {
    namespace factories {
        class LandscapeFactory : public GameObjectFactory
        {
        public:
            void build(GameWorld& gameWorld, AssetHolder& assetHolder, GameObject& gameObject) override;
        };
    }
}
}