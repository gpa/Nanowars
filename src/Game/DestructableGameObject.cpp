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

#include "Game/DestructableGameObject.hpp"
#include "Util/Box2DConverter.hpp"
#include <SFML/Graphics/Texture.hpp>
#include "Algorithms/ImagePainter.hpp"
#include "Core/Constants.hpp"

namespace nanowars {
namespace game {

    using namespace util;
    using sf::Texture;

    DestructableGameObject::DestructableGameObject(GameWorld& parent, b2Body& body, GameObjectType gameObjectType)
        : GameObject(parent, body, gameObjectType)
    {
    }

    void DestructableGameObject::initializeDestructableBehavior(const Image& textureSource)
    {
        for (b2Fixture* fixture = m_body.GetFixtureList(); fixture; fixture = fixture->GetNext())
        {
            if (fixture->GetShape()->GetType() != b2Shape::e_chain)
                throw std::invalid_argument("non-chain shapes are not supported.");

            b2ChainShape& chainShape = *static_cast<b2ChainShape*>(fixture->GetShape());
            CollisionRing collisionRing(chainShape.m_vertices, chainShape.m_vertices + chainShape.m_count);
            collisionRing.correct();
            m_fixtureCache.emplace_back(collisionRing, fixture);
        }
        m_textureSource = textureSource;
        m_wasInitialzied = true;
    }

    void DestructableGameObject::destroy(const DestructableGameObjectDestroyer& destroyer)
    {
        if (!m_wasInitialzied)
            return;

        destroyShape(destroyer);
        destroyTexture(destroyer);
    }

    void DestructableGameObject::destroyShape(const DestructableGameObjectDestroyer& destroyer)
    {
        auto destroyerCollisionRing = destroyer.getCollisionRing();
        auto destroyerAABB = destroyerCollisionRing.getAABB();

        int shapesCount = m_fixtureCache.size(); // important to cache this since we'll be adding shapes
        for (int i = 0; i < shapesCount; ++i)
        {
            if (m_fixtureCache[i].fixture == nullptr)
                continue;

            if (boost::geometry::intersects(m_fixtureCache[i].collisionRing.getAABB(), destroyerAABB))
            {
                vector<CollisionRing> subtractionResult = m_fixtureCache[i].collisionRing.getDifference(destroyerCollisionRing);

                if (subtractionResult.size() == 0)
                    continue;

                m_body.DestroyFixture(m_fixtureCache[i].fixture);
                m_fixtureCache[i].fixture = nullptr;

                for (int j = 0; j < subtractionResult.size(); ++j)
                {
                    CollisionRing simplified = subtractionResult[j].getSimplified(0.05f);

                    // bug workaround
                    if (simplified.getCount() == 2 && simplified[0] == simplified[1])
                        continue;

                    if (simplified.getArea() < 0.5f)
                        continue;

                    b2ChainShape chainShape;
                    chainShape.CreateChain(simplified.getVertices(), (int)simplified.getCount());
                    auto fixture = m_body.CreateFixture(&chainShape, 0.0f);

                    if (j != 0)
                        m_fixtureCache.emplace_back(simplified, fixture);
                    else
                    {
                        m_fixtureCache[i].fixture = fixture;
                        m_fixtureCache[i].collisionRing = simplified;
                    }
                }
            }
        }
    }

    void DestructableGameObject::destroyTexture(const DestructableGameObjectDestroyer& destroyer)
    {
        Image& img = m_textureSource;
        Image bmp;

        float sx = m_sprite.getScale().x;
        float sy = m_sprite.getScale().y;

        auto s = algorithms::ImagePainter::drawShape(destroyer.getCollisionRing(),
            sx, sy, core::constants::meterToPixelRatio, img, bmp, sf::Color(-1));

        algorithms::ImagePainter::scanLineFill(bmp, sf::Color(-1), sf::Color::Transparent);

        for (int y = 0; y < bmp.getSize().y; ++y)
        {
            for (int x = 0; x < bmp.getSize().x; ++x)
            {
                img.setPixel(s.x + x, s.y + y, bmp.getPixel(x, y));
            }
        }

        (const_cast<Texture*>(m_sprite.getTexture()))->update(bmp, s.x, s.y);
    }
}
}