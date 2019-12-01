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
            //for (int i = 0; i < 60; ++i)
            {
                b2ParticleDef pd;
                pd.lifetime = 1;
                pd.flags = b2_springParticle | b2_fixtureContactFilterParticle;

				//float random = Randomizer::getRandom(0.0f, 2 * b2_pi);
                //auto r = b2Vec2(std::sin(random), std::cos(random));
                // auto v = r * Randomizer::getRandom(0.0f, 0.001f);

                pd.velocity = vel;
                pd.position.Set(pos.x, pos.y);
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
