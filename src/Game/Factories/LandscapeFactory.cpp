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

#include "Game/Factories/LandscapeFactory.hpp"
#include "Game/GameObjects/Landscape.hpp"
#include "Algorithms/ImageToMapGenerator.hpp"
#include "Algorithms/CaveGenerator.hpp"
#include "Util/ImageAccessorSfmlImpl.hpp"
#include "Util/Box2DConverter.hpp"
#include "Core/Constants.hpp"
#include "Asset/Assets.hpp"

#include "Core/Constants.hpp"
#include <vector>

namespace nanowars {
namespace game {
    namespace factories {

        using namespace rapidjson;
        using namespace sf;
        using namespace std;
        using namespace util;
        using namespace core;
        using namespace algorithms;

        void LandscapeFactory::build(GameWorld& gameWorld, AssetHolder& assetHolder, GameObject& gameObject)
        {
            Landscape* landscape = static_cast<Landscape*>(&gameObject);
            auto& schema = assetHolder.getSchema(SchemaAsset::Landscape1);

            auto& texture = assetHolder.getUniqueTexture(TextureAsset::Landscape1);
            Image image = texture.copyToImage();

            b2Vec2 scale = { 1.f, 1.f };
            if (schema.HasMember(scaleProperty))
            {
                scale.x = schema[scaleProperty][xProperty].GetFloat();
                scale.y = schema[scaleProperty][xProperty].GetFloat();
            }

            ImageToMapGenerator ImageToMapGenerator(Vector2f(0.05f, 0.05f), 0.5f);
            auto collisionRings = ImageToMapGenerator.getCollisionRings(ImageAccessorSfmlImpl(image));

            for (auto& collisionRing : collisionRings)
            {
                for (size_t i = 0; i < collisionRing.getCount(); i++)
                {
                    b2Vec2 v = { collisionRing[i].x * scale.x, collisionRing[i].y * scale.y };
                    collisionRing[i] = v / constants::meterToPixelRatio;
                }

                b2ChainShape chain;
                auto* vertices = collisionRing.getVertices();
                chain.CreateChain(vertices, (int)collisionRing.getCount());
                landscape->getBody().CreateFixture(&chain, 0.0f);
            }

            landscape->getBody().SetType(b2BodyType::b2_staticBody);

            landscape->initializeDestructableBehavior(image);

            const Value& areasSchema = schema[areasProperty];

            for (SizeType k = 0; k < areasSchema.Size(); ++k)
            {
                const Value& areaSchema = areasSchema[k];
                LandscapeArea landscapeArea;
                b2AABB aabb;

                aabb.lowerBound = b2Vec2(
                    areaSchema[lowerBoundProperty][xProperty].GetFloat() / constants::meterToPixelRatio * scale.x,
                    areaSchema[lowerBoundProperty][yProperty].GetFloat() / constants::meterToPixelRatio * scale.y);

                aabb.upperBound = b2Vec2(
                    areaSchema[upperBoundProperty][xProperty].GetFloat() / constants::meterToPixelRatio * scale.x,
                    areaSchema[upperBoundProperty][yProperty].GetFloat() / constants::meterToPixelRatio * scale.y);

                auto test = areaSchema["type"].GetString();

                landscapeArea.area = aabb;
                landscapeArea.type = LandscapeArea::LandscapeAreaType::Launchpad;

                landscape->addArea(landscapeArea);
            }

            auto& sprite = landscape->getSprite();
            sprite.setTexture(texture);
            sprite.setOrigin(0, 0);
            sprite.setScale(scale.x, scale.y);
        }
    }
}
}
