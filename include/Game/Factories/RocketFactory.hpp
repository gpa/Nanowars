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

#include "Game/GameWorld.hpp"
#include "Game/Factories/GameObjectFactory.hpp"
#include "Game/GameObjects/Rocket.hpp"

namespace nanowars {
namespace game {
    namespace factories {
        class RocketFactory : public GameObjectFactory
        {
        public:
            void build(GameWorld& gameWorld, AssetHolder& assetHolder, GameObject& gameObject) override;

        protected:
            static constexpr auto xDirectionProperty = "vx";
            static constexpr auto yDirectionProperty = "vy";
            static constexpr auto enginesProperty = "engines";
            static constexpr auto weaponSlotsProperty = "weapon_slots";
            static constexpr auto mainEngineTypeProperty = "mainEngine";
            static constexpr auto engineTypeProperty = "engineType";
            static constexpr auto leftEngineTypeProperty = "positionalLeftEngine";
            static constexpr auto rightEngineTypeProperty = "positionalRightEngine";
        };
    }
}
}
