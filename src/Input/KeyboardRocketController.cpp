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

#include "Input/KeyboardRocketController.hpp"

namespace nanowars {
namespace input {

    KeyboardRocketController::KeyboardRocketController(KeyboardRocketControllerConfiguration keyboardConfiguration)
        : m_keyboardConfiguration(keyboardConfiguration)
    {
    }

    bool KeyboardRocketController::handleContinuousEvent(const Mouse& mouse, const Keyboard& keyboard)
    {
        bool reacted = false;
        if (keyboard.isKeyPressed(m_keyboardConfiguration.thrust))
        {
            fly();
            reacted = true;
        }
        if (keyboard.isKeyPressed(m_keyboardConfiguration.left))
        {
            flyLeft();
            reacted = true;
        }
        if (keyboard.isKeyPressed(m_keyboardConfiguration.right))
        {
            flyRight();
            reacted = true;
        }
        if (keyboard.isKeyPressed(m_keyboardConfiguration.shoot))
        {
            shoot();
            reacted = true;
        }

        return reacted;
    }
}
}
