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

#include "Graphics/GameRenderer.hpp"
#include "Graphics/FollowingCamera.hpp"

namespace nanowars {
namespace graphics {

    GameRenderer::GameRenderer(shared_ptr<Game> game, Entity* focusedEntity)
        : m_game(game)
    {
        m_activeCamera = std::make_shared<FollowingCamera>(40.f);
        static_cast<FollowingCamera*>(m_activeCamera.get())->follow(focusedEntity);
    }

    void GameRenderer::render(sf::RenderWindow& window)
    {
        if (m_activeCamera)
            window.setView(m_activeCamera->getView());

        for (const auto& Entity : m_game->getGameWorld().getEntities())
            window.draw(*Entity.get());
    }
}
}
