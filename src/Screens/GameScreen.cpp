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

#include "Screens/GameScreen.hpp"
#include "Game/Factories/RocketFactory.hpp"
#include "Game/Factories/LandscapeFactory.hpp"
#include "Game/Factories/BulletFactory.hpp"

namespace nanowars {
namespace screens {

    using namespace factories;

    GameScreen::GameScreen(AssetContainer assetContainer)
        : m_gameWorld(assetContainer.getNewContainer())
        , m_followingCamera(40.0f)
        , m_keyboardRocketController(KeyboardRocketControllerConfiguration())
    {

        m_gameWorld.registerFactory<Landscape>(std::make_shared<LandscapeFactory>());
        m_gameWorld.registerFactory<Rocket>(std::make_shared<RocketFactory>());
        m_gameWorld.registerFactory<Bullet>(std::make_shared<BulletFactory>());

        Rocket* rocket = m_gameWorld.spawn<Rocket>();
        Landscape* landscape = m_gameWorld.spawn<Landscape>();

        m_followingCamera.follow(rocket);
        m_keyboardRocketController.setRocket(rocket);
        m_activeCamera = &m_followingCamera;
    }

    void GameScreen::update(float dt)
    {
        m_gameWorld.step(dt);
    }

    bool GameScreen::handleEvent(const Event& event)
    {
        return false;
    }

    bool GameScreen::handleContinuousEvent(const Mouse& mouse, const Keyboard& keyboard)
    {
        return m_keyboardRocketController.handleContinuousEvent(mouse, keyboard);
    }

    void GameScreen::render(RenderWindow& window)
    {
        window.setView(m_activeCamera->getView());

        for (const auto& gameObject : m_gameWorld.getGameObjects())
        {
            window.draw(*gameObject.get());
        }
    }
}
}