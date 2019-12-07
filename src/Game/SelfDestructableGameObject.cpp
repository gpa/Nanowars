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

#include "Game/SelfDestructableGameObject.hpp"
#include "Game/GameWorld.hpp"

namespace nanowars {
namespace game {

    SelfDestructableGameObject::SelfDestructableGameObject(GameWorld& parent, b2Body& body, GameObjectType type, float lifetimeInSeconds)
        : GameObject(parent, body, type)
        , m_lifetimeInSeconds(lifetimeInSeconds)
    {
    }

    void SelfDestructableGameObject::update(float dt)
    {
        if (m_lifetimeClock.getElapsedTime().asSeconds() > m_lifetimeInSeconds)
            m_parent.kill(*this);
    }
}
}