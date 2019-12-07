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

#include "Gameplay/Entity.hpp"
#include "Gameplay/GameWorld.hpp"
#include "Core/Constants.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace nanowars {
namespace gameplay {

    Entity::Entity(GameWorld& parent, b2Body& body, EntityType type)
        : m_parent(parent)
        , m_body(body)
        , m_type(type)
    {
        m_body.SetUserData(static_cast<void*>(this));
        m_body.SetType(b2BodyType::b2_dynamicBody);
    }

    EntityType Entity::getType() const
    {
        return m_type;
    }

    b2Body& Entity::getBody()
    {
        return m_body;
    }

    Sprite& Entity::getSprite()
    {
        return m_sprite;
    }

    void Entity::onCollision(Entity& other)
    {
    }

    void Entity::update(float dt)
    {
    }

    void Entity::draw(RenderTarget& target, RenderStates states) const
    {
        b2Vec2 bodyPos = m_body.GetPosition();

        auto position = sf::Vector2f(bodyPos.x * core::constants::meterToPixelRatio, bodyPos.y * core::constants::meterToPixelRatio);
        float angle = m_body.GetAngle() * (180 / b2_pi);

        m_sprite.setPosition(position.x, position.y);
        m_sprite.setRotation(angle);

        target.draw(m_sprite);
    }
}
}
