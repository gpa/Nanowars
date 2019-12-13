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

#include "Gameplay/Entity.hpp"
#include "Gameplay/Players/Player.hpp"
#include <memory>

namespace nanowars {
namespace gameplay {
    namespace controllers {

        using namespace players;
        using std::shared_ptr;

        class EntityController
        {
        public:
            EntityController(shared_ptr<Player> owner)
                : m_controlledEntity(nullptr)
                , m_owner(owner)
            {
            }

            EntityController() = delete;
            EntityController(const EntityController&) = delete;
            EntityController& operator=(const EntityController&) = delete;

            inline void setEntity(Entity* entity) { m_controlledEntity = entity; }
            inline Entity* getEntity() { return m_controlledEntity; }
            inline bool hasEntity() const { return m_controlledEntity != nullptr; }
            inline void resetEntity() { m_controlledEntity = nullptr; }

            inline Player& getPlayer() { return m_owner.get(); }

        protected:
            shared_ptr<Player> m_owner;
            Entity* m_controlledEntity;
        };
    }
}
}