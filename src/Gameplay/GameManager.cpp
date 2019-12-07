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

#include "Gameplay/GameManager.hpp"
#include "Gameplay/Games/DeathmatchGame.hpp"

namespace nanowars {
namespace gameplay {

    using namespace factories;
    using namespace games;

    GameManager::GameManager(AssetHolder&& assetHolder)
        : m_assetHolder(std::move(assetHolder))
    {
    }

    void GameManager::startGame()
    {
        if (isGameRunning())
            throw new std::logic_error("A game is already running.");

        m_gameWorld = std::make_shared<GameWorld>(m_assetHolder);
        DeathmatchGame game(*this, *m_gameWorld.get(), m_assetHolder, GameInfo());
        game.initialize();

        /*auto rocketController = static_cast<RocketController*>(game.getEntityControllers()[0].get());
		auto rocket = static_cast<Rocket*>(game.getEntityControllers()[0]->getEntity());
        m_activeCamera = std::make_shared<FollowingCamera>(40.0f);
        static_cast<FollowingCamera*>(m_activeCamera.get())->follow(rocket);
        m_inputMapping.addRealtimeMapping(sf::Keyboard::Up, std::bind(&RocketController::fly, this, std::placeholders::_1);*/
    }

    void GameManager::exitGame()
    {
        m_gameWorld = nullptr;
    }

    bool GameManager::isGameRunning()
    {
        return m_gameWorld.get() != nullptr;
    }

    void GameManager::update(float dt)
    {
        if (m_gameWorld)
            m_gameWorld->step(dt);
    }

    bool GameManager::handleEvent(const Event& event)
    {
        return false;
    }

    bool GameManager::handleContinuousEvent(const Mouse& mouse, const Keyboard& keyboard)
    {
        return false;
    }

    void GameManager::render(RenderWindow& window)
    {
        if (!m_gameWorld)
            return;

        if (m_activeCamera)
            window.setView(m_activeCamera->getView());

        for (const auto& Entity : m_gameWorld->getEntities())
            window.draw(*Entity.get());
    }
}
}