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
#include "Util/ImageAccessorSfmlImpl.hpp"
#include "Util/Box2DConverter.hpp"
#include "Assets/Assets.hpp"

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

            auto& texture = assetHolder.getUniqueTexture(TextureAsset_Landscape1);
            Image img = texture.copyToImage();

            b2Vec2 scale = { 25.0f, 40.0f };

            ImageToMapGenerator ImageToMapGenerator(Vector2f(0.05f, 0.05f), 0.5f);
            auto collisionRings = ImageToMapGenerator.getCollisionRings(ImageAccessorSfmlImpl(img));

            for (auto& collisionRing : collisionRings)
            {
                for (size_t i = 0; i < collisionRing.getCount(); i++)
                {
                    b2Vec2 v = { collisionRing[i].x * scale.x, collisionRing[i].y * scale.y };
                    collisionRing[i] = v / constants::meterToPixelRatio;
                }

                b2ChainShape chain = Box2DConverter::collisionRingToChainShape(collisionRing);
                landscape->getBody().CreateFixture(&chain, 0.0f);
            }

            landscape->getBody().SetType(b2BodyType::b2_staticBody);

            landscape->initializeDestructableBehavior(img);

            auto& sprite = landscape->getSprite();
            sprite.setTexture(texture);
            sprite.setOrigin(0, 0);
            sprite.setScale(scale.x, scale.y);
        }
    }
}
}
