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

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

namespace nanowars {
namespace gameplay {
    namespace particles {

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
