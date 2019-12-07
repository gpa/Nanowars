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
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>

#include <functional>
#include <map>

namespace nanowars {
namespace input {

    using sf::Event;
    using sf::Mouse;
    using sf::Keyboard;

    enum class InputMappingType
    {
        Press,
        Release,
        Hold
    };

    class InputMapping
    {
    public:
        typedef std::function<void()> eventHandler_t;

        void processInput(sf::Window& window);

        void addRealtimeMapping(sf::Keyboard::Key key, eventHandler_t handler);
        void addRealtimeMapping(sf::Mouse::Button button, eventHandler_t handler);

        void removeRealtimeMapping(sf::Keyboard::Key key, InputMappingType inputMappingType);
        void removeRealtimeMapping(sf::Mouse::Button button, InputMappingType inputMappingType);

    private:
        template <typename T>
        struct InputBinding
        {
            T trigger;
            eventHandler_t handler;
        };

        std::vector<InputBinding<sf::Keyboard::Key>> m_realtimeKeyboardMapping;
        std::vector<InputBinding<sf::Mouse::Button>> m_realtimeMouseMapping;
    };
}
}