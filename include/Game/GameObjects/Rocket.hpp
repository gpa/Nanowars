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
#include "Game/Decorations/ThrustParticleSystem.hpp"
#include <Box2D/Box2D.h>
#include <vector>

namespace nanowars {
namespace game {

    using std::vector;
	using namespace decorations;

    struct RocketEngine
    {
        enum class EngineType
        {
            Main,
            PositionalLeft,
            PositionalRight
        } type;

        b2Vec2 position;
        b2Vec2 force;
    };

    struct RocketWeaponSlot
    {
        b2Vec2 position;
        b2Vec2 direction;
    };

    class Rocket : public GameObject
    {
    public:
        Rocket(GameWorld& parent, b2Body& body);
        void setEquipment(vector<RocketEngine> engines, vector<RocketWeaponSlot> weaponSlots);

        void shoot();
        void applyMainThrust();
        void applyLeftThrust();
        void applyRightThrust();

    private:
        void applyThrustFromEngines(RocketEngine::EngineType type);
        void draw(RenderTarget& target, RenderStates states) const override;

        vector<RocketEngine> m_engines;
        vector<RocketWeaponSlot> m_weaponSlots;
        ThrustParticleSystem m_thrustParticleSystem;
    };
}
}