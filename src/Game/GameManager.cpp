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
        , m_gameWorld(m_assetHolder)
        , m_followingCamera(40.0f)
        , m_keyboardRocketController(KeyboardRocketControllerConfiguration())
        , m_activeCamera(nullptr)
        , m_isGameInProgress(false)
    {
        m_gameWorld.registerFactory<Landscape>(std::make_shared<LandscapeFactory>());
        m_gameWorld.registerFactory<Rocket>(std::make_shared<RocketFactory>());
        m_gameWorld.registerFactory<Bullet>(std::make_shared<BulletFactory>());
    }

    void GameManager::startGame()
    {
        if (m_isGameInProgress)
            return;
            
        Landscape* landscape = m_gameWorld.spawn<Landscape>();
        Rocket* rocket = m_gameWorld.spawn<Rocket>();

        rocket->getBody().SetTransform(b2Vec2(50.0f, 0.0f), 0.0f);

        m_followingCamera.follow(rocket);
        m_keyboardRocketController.setRocket(rocket);
        m_activeCamera = &m_followingCamera;
        m_isGameInProgress = true;
    }

    void GameManager::exitGame()
    {
        m_followingCamera.follow(nullptr);
        m_keyboardRocketController.setRocket(nullptr);
        m_gameWorld.reset();
        m_isGameInProgress = false;
    }

    bool GameManager::isGameRunning()
    {
        return m_isGameInProgress;
    }

    void GameManager::update(float dt)
    {
        m_gameWorld.step(dt);
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
        if (m_activeCamera != nullptr)
            window.setView(m_activeCamera->getView());

        for (const auto& gameObject : m_gameWorld.getGameObjects())
        {
            window.draw(*gameObject.get());
        }
    }
}
}