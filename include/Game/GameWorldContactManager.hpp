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
#include <Box2D/Box2D.h>
#include <vector>

namespace nanowars {
namespace game {

    using std::vector;
    using std::pair;

    class GameWorldContactManager : public b2ContactFilter, public b2ContactListener
    {
    public:
        bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) override;
        bool ShouldCollide(b2Fixture* fixture, b2ParticleSystem* particleSystem, int32 particleIndex) override;
        bool ShouldCollide(b2ParticleSystem* particleSystem, int32 particleIndexA, int32 particleIndexB) override;

        void BeginContact(b2Contact* c) override;
        void ProcessContacts();

    private:
        vector<pair<GameObject*, GameObject*>> m_collisionCache;
    };
}
}
