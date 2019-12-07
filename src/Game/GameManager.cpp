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

#include "Game/GameManager.hpp"
#include "Game/Factories/RocketFactory.hpp"
#include "Game/Factories/LandscapeFactory.hpp"
#include "Game/Factories/BulletFactory.hpp"

namespace nanowars {
namespace game {

    using namespace factories;

    GameManager::GameManager(AssetHolder&& assetHolder)
        : m_assetHolder(std::move(assetHolder))
        , m_keyboardRocketController(KeyboardRocketControllerConfiguration())
    {
    }

    void GameManager::startGame()
    {
        if (isGameRunning())
            throw new std::logic_error("A game is already running.");

        m_gameWorld = std::make_shared<GameWorld>(m_assetHolder);
		m_gameWorld->registerFactory<Landscape>(std::make_shared<LandscapeFactory>());
        m_gameWorld->registerFactory<Rocket>(std::make_shared<RocketFactory>());
        m_gameWorld->registerFactory<Bullet>(std::make_shared<BulletFactory>());

        Landscape* landscape = m_gameWorld->spawn<Landscape>();
        for (auto& area : landscape->getAreas())
        {
            Rocket* rocket = m_gameWorld->spawn<Rocket>();
            rocket->getBody().SetTransform(area.area.GetCenter(), 0.0f);

			m_activeCamera = std::make_shared<FollowingCamera>(40.0f);
            static_cast<FollowingCamera*>(m_activeCamera.get())->follow(rocket);
            m_keyboardRocketController.setRocket(rocket);
        }
    }

    void GameManager::exitGame()
    {
        m_keyboardRocketController.setRocket(nullptr);
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
        return m_keyboardRocketController.handleContinuousEvent(mouse, keyboard);
    }

    void GameManager::render(RenderWindow& window)
    {
        if (!m_gameWorld)
            return;
		
		if (m_activeCamera)
            window.setView(m_activeCamera->getView());

        for (const auto& gameObject : m_gameWorld->getGameObjects())
            window.draw(*gameObject.get());
    }
}
}