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

#include "Game/Factories/RocketFactory.hpp"
#include "Game/GameObjects/Rocket.hpp"
#include "Core/Constants.hpp"

#include <rapidjson/document.h>

#include <vector>

namespace nanowars {
namespace game {
    namespace factories {

        using namespace rapidjson;
        using namespace sf;
        using namespace std;

        void RocketFactory::build(GameWorld& gameWorld, AssetHolder& assetHolder, GameObject& gameObject)
        {
            Rocket* rocket = static_cast<Rocket*>(&gameObject);

            const auto& texture = assetHolder.getTexture(TextureAsset_Rockets);
            const Document& schema = assetHolder.getSchema(SchemaAsset_Rocket1);
            float scale = schema.HasMember(scaleProperty) ? schema[scaleProperty].GetFloat() : 1.0f;

            vector<RocketEngine> engines;
            const Value& enginesSchema = schema[enginesProperty];
            for (SizeType k = 0; k < enginesSchema.Size(); ++k)
            {
                const Value& engineSchema = enginesSchema[k];

                RocketEngine rocketEngine;
                rocketEngine.position.x = -engineSchema[xPositionProperty].GetFloat() * scale;
                rocketEngine.position.y = -engineSchema[yPositionProperty].GetFloat() * scale;
                rocketEngine.force.x = -engineSchema[xDirectionProperty].GetFloat();
                rocketEngine.force.y = -engineSchema[yDirectionProperty].GetFloat();

                string type = engineSchema[engineTypeProperty].GetString();
                if (type == mainEngineTypeProperty)
                {
                    rocketEngine.type = RocketEngine::EngineType::Main;
                }
                else if (type == leftEngineTypeProperty)
                {
                    rocketEngine.type = RocketEngine::EngineType::PositionalLeft;
                }
                else if (type == rightEngineTypeProperty)
                {
                    rocketEngine.type = RocketEngine::EngineType::PositionalRight;
                }
                engines.push_back(rocketEngine);
            }

            vector<RocketWeaponSlot> weaponSlots;
            const Value& weaponSchema = schema[weaponSlotsProperty];
            for (SizeType k = 0; k < weaponSchema.Size(); ++k)
            {
                const Value& slotSchema = weaponSchema[k];
                RocketWeaponSlot slot;
                slot.position.x = -slotSchema[xPositionProperty].GetFloat() * scale;
                slot.position.y = -slotSchema[yPositionProperty].GetFloat() * scale;
                slot.direction.x = -slotSchema[xDirectionProperty].GetFloat();
                slot.direction.y = -slotSchema[yDirectionProperty].GetFloat();
                weaponSlots.push_back(slot);
            }

            rocket->setEquipment(engines, weaponSlots);

            auto& body = rocket->getBody();
            body.SetType(b2BodyType::b2_dynamicBody);

            auto scaleRect = GameObjectFactory::createFixturesFromSchema(schema, body, Vector2f(scale, scale));

            auto& textureSchema = schema[textureProperty];

            IntRect textureRect;
            textureRect.left = textureSchema[textureRectLeftProperty].GetInt();
            textureRect.top = textureSchema[textureRectTopProperty].GetInt();
            textureRect.width = textureSchema[textureRectWidthProperty].GetInt();
            textureRect.height = textureSchema[textureRectHeightProperty].GetInt();

            rocket->getSprite().setTextureRect(textureRect);
            createSpriteFromTexture(rocket->getSprite(), texture, scaleRect);
        }
    }
}
}
