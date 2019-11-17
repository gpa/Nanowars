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
#include "Algorithms/LaunchPadFinder.hpp"

namespace nanowars {
namespace game {

    using namespace factories;

    GameManager::GameManager(AssetHolder&& assetHolder)
        : m_gameWorld(assetHolder.getNewHolder())
        , m_followingCamera(40.0f)
        , m_keyboardRocketController(KeyboardRocketControllerConfiguration())
    {

        m_gameWorld.registerFactory<Landscape>(std::make_shared<LandscapeFactory>());
        m_gameWorld.registerFactory<Rocket>(std::make_shared<RocketFactory>());
        m_gameWorld.registerFactory<Bullet>(std::make_shared<BulletFactory>());

        Landscape* landscape = m_gameWorld.spawn<Landscape>();
        Rocket* rocket = m_gameWorld.spawn<Rocket>();

        auto launchPadPositions = algorithms::LaunchPadFinder::getBestLaunchPodPositions(landscape->getBody());
        rocket->getBody().SetTransform(launchPadPositions[0], 0.0f);

        m_followingCamera.follow(rocket);
        m_keyboardRocketController.setRocket(rocket);
        m_activeCamera = &m_followingCamera;
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
        window.setView(m_activeCamera->getView());

        for (const auto& gameObject : m_gameWorld.getGameObjects())
        {
            window.draw(*gameObject.get());
        }
    }
}
}