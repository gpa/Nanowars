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

#include "Input/InputMapping.hpp"
#include <SFML/Window/Window.hpp>
#include <algorithm>

namespace nanowars {
namespace input {

    void InputMapping::addRealtimeMapping(sf::Keyboard::Key key, eventHandler_t handler)
    {
        InputBinding<sf::Keyboard::Key> binding;
        binding.trigger = key;
        binding.handler = handler;
        m_realtimeKeyboardMapping.push_back(binding);
    }

    void InputMapping::addRealtimeMapping(sf::Mouse::Button button, eventHandler_t handler)
    {
        InputBinding<sf::Mouse::Button> binding;
        binding.trigger = button;
        binding.handler = handler;
        m_realtimeMouseMapping.push_back(binding);
    }

    void InputMapping::removeRealtimeMapping(sf::Keyboard::Key key, InputMappingType inputMappingType)
    {
    }

    void InputMapping::removeRealtimeMapping(sf::Mouse::Button button, InputMappingType inputMappingType)
    {
    }

    void InputMapping::processInput(sf::Window& window)
    {
        for (const auto& inputBinding : m_realtimeMouseMapping)
            if (sf::Mouse::isButtonPressed(inputBinding.trigger))
                inputBinding.handler();

        for (const auto& inputBinding : m_realtimeKeyboardMapping)
            if (sf::Keyboard::isKeyPressed(inputBinding.trigger))
                inputBinding.handler();
    }
}
}