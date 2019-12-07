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

#include <Box2D/Box2D.h>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Gameplay/EntityType.hpp"

namespace nanowars {
namespace gameplay {

    using sf::Drawable;
    using sf::Sprite;
    using sf::RenderTarget;
    using sf::RenderStates;

    class GameWorld;
    class Entity : public Drawable
    {
    public:
        Entity(GameWorld& parent, b2Body& body, EntityType type);

        Sprite& getSprite();
        b2Body& getBody();

        EntityType getType() const;

        virtual void onCollision(Entity& other);
        virtual void update(float dt);

    protected:
        virtual void draw(RenderTarget& target, RenderStates states) const override;

        b2Body& m_body;
        GameWorld& m_parent;
        mutable Sprite m_sprite;
        const EntityType m_type;
    };
}
}