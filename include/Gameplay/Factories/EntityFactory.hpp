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

#include "Gameplay/Entity.hpp"
#include "Math/Vector2.hpp"
#include "Asset/AssetHolder.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <rapidjson/document.h>

namespace nanowars {
namespace gameplay {

    using namespace asset;

    class GameWorld;
    namespace factories {

        class EntityFactory
        {
        public:
            virtual void build(GameWorld& gameWorld, AssetHolder& assetHolder, Entity& Entity) = 0;

        protected:
            static constexpr auto scaleProperty = "scale";
            static constexpr auto shapeProperty = "shape";
            static constexpr auto rotationInteriaProperty = "rotation_interia";
            static constexpr auto massProperty = "mass";
            static constexpr auto massCenterProperty = "mass_center";
            static constexpr auto frictionProperty = "friction";
            static constexpr auto densityProperty = "density";
            static constexpr auto restitutionProperty = "restitution";
            static constexpr auto linearDampingProperty = "linear_damping";
            static constexpr auto rotationalDampingProperty = "rotational_damping";
            static constexpr auto gravityScaleProperty = "gravity_scale";
            static constexpr auto xProperty = "x";
            static constexpr auto yProperty = "y";
            static constexpr auto vxProperty = "vx";
            static constexpr auto vyProperty = "vy";
            static constexpr auto textureProperty = "texture";
            static constexpr auto textureRectLeftProperty = "left";
            static constexpr auto textureRectTopProperty = "top";
            static constexpr auto textureRectWidthProperty = "width";
            static constexpr auto textureRectHeightProperty = "height";
            static constexpr auto lowerBoundProperty = "lowerBound";
            static constexpr auto upperBoundProperty = "upperBound";

			// game entity dependent
            static constexpr auto areasProperty = "areas";
            static constexpr auto enginesProperty = "engines";
            static constexpr auto weaponSlotsProperty = "weapon_slots";
            static constexpr auto mainEngineTypeProperty = "mainEngine";
            static constexpr auto engineTypeProperty = "engineType";
            static constexpr auto leftEngineTypeProperty = "positionalLeftEngine";
            static constexpr auto rightEngineTypeProperty = "positionalRightEngine";

            static sf::Sprite createSpriteFromTexture(sf::Sprite& s, const sf::Texture& texture, sf::FloatRect scaleRect);
            static sf::FloatRect createFixturesFromSchema(const rapidjson::Document& document, b2Body& body, sf::Vector2f scale);
        };
    }
}
}