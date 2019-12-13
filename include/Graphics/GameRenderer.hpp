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

#include "Gameplay/Games/Game.hpp"
#include "Debug/DebugManager.hpp"
#include "Gameplay/Controllers/EntityController.hpp"
#include "Graphics/Camera.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

namespace nanowars {
namespace graphics {

    using namespace games;
    using namespace controllers;

    class GameRenderer
    {
    public:
        GameRenderer(shared_ptr<Game> game);
        void render(sf::RenderWindow& window);

        void setView(EntityController* entityController);

    private:
        shared_ptr<Game> m_game;
        shared_ptr<Camera> m_activeCamera;

        friend class debug::DebugManager;
    };
}
}