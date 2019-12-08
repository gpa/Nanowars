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

#include "Gameplay/Games/GameType.hpp"

namespace nanowars {
namespace gameplay {
    namespace games {

        enum class GameState
        {
            HasNotStarted,
            IsRunning,
            IsFinished,
            IsPaused
        };

        struct GameInfo
        {
            GameType type;
            GameState state;

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