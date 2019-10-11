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

#include "Game/GameObject.hpp"
#include "Game/DestructableGameObjectDestroyer.hpp"

namespace nanowars {
namespace game {

    class Rocket;
    class GameWorld;

    class Bullet : public GameObject, public DestructableGameObjectDestroyer
    {
    public:
        Bullet(GameWorld& parent, b2Body& body, Rocket* firedBy, b2Vec2 position, b2Vec2 velocity);

        void onCollision(GameObject& other) override;
        CollisionRing getCollisionRing() const override;

        Rocket* getFiredBy();

    private:
        void draw(RenderTarget& target, RenderStates states) const override;

        Rocket* m_firedBy;
    };
}
}