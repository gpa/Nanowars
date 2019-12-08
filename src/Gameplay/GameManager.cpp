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

    GameManager::GameManager(AssetHolder&& assetHolder, const ConfigManager& configManager)
        : m_assetHolder(std::move(assetHolder))
        , m_gameRenderer(nullptr, nullptr)
        , m_configManager(configManager)
    {
    }

    void GameManager::setGame(GameInfo gameInfo)
    {
        if (gameInfo.type == GameType::NoGame)
        {
            m_game = nullptr;
            return;
        }

        m_game = std::make_shared<DeathmatchGame>(m_assetHolder, gameInfo);
        m_game->initialize();
        RocketController& rocketController = *(static_cast<RocketController*>((m_game->getEntityControllers()[0].get())));
        m_gameRenderer = GameRenderer(m_game, rocketController.getEntity());

        m_inputManager.bindToControllerViaConfiguration(rocketController, m_configManager, false);
    }

    const GameInfo& GameManager::getGame() const
    {
        if (!m_game)
            return m_noGameInfo;

        return m_game->getGameInfo();
    }

    void GameManager::update(float dt)
    {
        if (m_game)
            m_game->update(dt);
    }

    void GameManager::handleInput(InputQueue& inputQueue)
    {
        m_inputManager.processInput(inputQueue);
    }

    void GameManager::render(RenderWindow& window)
    {
        if (!m_game)
            return;

        m_gameRenderer.render(window);
    }
}
}