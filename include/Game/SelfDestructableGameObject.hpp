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
#include <SFML/System/Clock.hpp>

namespace nanowars {
namespace game {

    class SelfDestructableGameObject : public GameObject
    {
    public:
        SelfDestructableGameObject(GameWorld& parent, b2Body& body, GameObjectType type, float lifetimeInSeconds);
		void update(float dt) override;

    private:
		sf::Clock m_lifetimeClock;
        float m_lifetimeInSeconds;
    };
}
}