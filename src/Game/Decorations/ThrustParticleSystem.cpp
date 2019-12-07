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

#include "Game/Decorations/ThrustParticleSystem.hpp"
#include "Game/GameWorld.hpp"
#include "Core/Constants.hpp"
#include "Algorithms/Randomizer.hpp"

namespace nanowars {
namespace game {
    namespace decorations {

        using namespace core;
        using namespace algorithms;

        ThrustParticleSystem::ThrustParticleSystem(b2Body& parent)
            : m_parent(parent)
        {
            b2ParticleSystemDef particleSystemDef;
            particleSystemDef.elasticStrength = 40;
            particleSystemDef.radius = 4 / 30.0f;

            m_system = m_parent.GetWorld()->CreateParticleSystem(&particleSystemDef);
            m_system->SetStrictContactCheck(true);
        }

        void ThrustParticleSystem::draw(RenderTarget& target, RenderStates states) const
        {
        }

        void ThrustParticleSystem::fire(b2Vec2 pos, b2Vec2 vel)
        {
            for (int i = 0; i < 60; ++i)
            {
                b2ParticleDef pd;
                pd.lifetime = Randomizer::getRandom(0.2f, 0.4f);
                pd.flags = b2_springParticle | b2_fixtureContactFilterParticle;

                float random1 = Randomizer::getRandom(0.0f, 2.0f);
                float random2 = Randomizer::getRandom(0.0f, 2.0f);

                float random = Randomizer::getRandom(0.0f, 2 * b2_pi);
                auto randomDir = b2Vec2(std::sin(random), std::cos(random));
                auto distortion = randomDir * Randomizer::getRandom(0.0f, 1.0f);

                float angleRad = m_parent.GetAngle() * b2_pi / 180.f;
                auto direction = b2Vec2(std::cos(angleRad), std::sin(angleRad));

                pd.position = pos + distortion;
                pd.velocity = vel + direction * (-90.f) + distortion * 30.f;

                m_system->CreateParticle(pd);
            }
        }

        ThrustParticleSystem::~ThrustParticleSystem()
        {
            m_parent.GetWorld()->DestroyParticleSystem(m_system);
        }
    }
}
}
