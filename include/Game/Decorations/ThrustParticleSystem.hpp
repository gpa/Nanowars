#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

namespace nanowars {
namespace game {
    namespace decorations {

		using sf::Drawable;

        class ThrustParticleSystem : public sf::Drawable
        {
        public:
            ThrustParticleSystem(b2Body& parent);
            ~ThrustParticleSystem();

            void fire(b2Vec2 pos, b2Vec2 vel);
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        private:
            b2ParticleSystem* m_system;
            b2Body& m_parent;
        };

    }
}
}
