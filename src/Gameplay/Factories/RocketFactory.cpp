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

#include "Gameplay/Factories/RocketFactory.hpp"
#include "Gameplay/Entities/Rocket.hpp"
#include "Core/Constants.hpp"

#include <rapidjson/document.h>

#include <vector>

namespace nanowars {
namespace gameplay {
    namespace factories {

        using namespace entities;
        using namespace rapidjson;
        using namespace sf;
        using namespace std;

        void RocketFactory::build(GameWorld& gameWorld, AssetHolder& assetHolder, Entity& Entity)
        {
            Rocket* rocket = static_cast<Rocket*>(&Entity);

            const auto& texture = assetHolder.getTexture(TextureAsset::Rockets1);
            const Document& schema = assetHolder.getSchema(SchemaAsset::Rocket1);
            float scale = schema.HasMember(scaleProperty) ? schema[scaleProperty].GetFloat() : 1.0f;

            vector<RocketEngine> engines;
            const Value& enginesSchema = schema[enginesProperty];
            for (SizeType k = 0; k < enginesSchema.Size(); ++k)
            {
                const Value& engineSchema = enginesSchema[k];

                RocketEngine rocketEngine;
                rocketEngine.position.x = -engineSchema[xProperty].GetFloat() * scale;
                rocketEngine.position.y = -engineSchema[yProperty].GetFloat() * scale;
                rocketEngine.force.x = -engineSchema[vxProperty].GetFloat();
                rocketEngine.force.y = -engineSchema[vyProperty].GetFloat();

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
                slot.position.x = -slotSchema[xProperty].GetFloat() * scale;
                slot.position.y = -slotSchema[yProperty].GetFloat() * scale;
                slot.direction.x = -slotSchema[vxProperty].GetFloat();
                slot.direction.y = -slotSchema[vyProperty].GetFloat();
                weaponSlots.push_back(slot);
            }

            rocket->setEquipment(engines, weaponSlots);

            auto& body = rocket->getBody();
            body.SetType(b2BodyType::b2_dynamicBody);

            auto scaleRect = EntityFactory::createFixturesFromSchema(schema, body, Vector2f(scale, scale));

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
