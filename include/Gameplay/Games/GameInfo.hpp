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

#include "Gameplay/Players/Player.hpp"
#include <memory>
#include <vector>

namespace nanowars {
namespace gameplay {
    namespace games {

        using std::vector;
        using std::shared_ptr;
        using players::Player;

        enum class GameState
        {
            HasNotStarted,
            IsRunning,
            IsFinished,
            IsPaused
        };

        enum class GameType
        {
            NoGame,
            Deathmatch
        };

        struct DeathmatchGameInfo
        {
            float gameTimeout;
            float respawnTimeout;
            int killsTimeout;
        };

        struct GameInfo
        {
            GameType type;
            GameState state;
            vector<shared_ptr<Player>> players;

         //   union
          //  {
                DeathmatchGameInfo deathmatchGameInfo;
          //  };

            GameInfo()
                : GameInfo(GameType::NoGame)
            {
            }

            GameInfo(GameType type)
                : type(type)
                , state(GameState::HasNotStarted)
            {
            }
        };
    }
}
}