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
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

namespace nanowars {
namespace input {

    using sf::Window;
    using sf::Event;
    using sf::Mouse;
    using sf::Keyboard;
    using std::vector;

    class InputQueue
    {
    public:
        InputQueue();
        void consume(Window& window);

        bool canConsumeRealtimeMouseInput();
        sf::Mouse& consumeRealtimeMouseInput();

        bool canConsumeRealtimeKeyboardInput();
        sf::Keyboard& consumeRealtimeKeyboardInput();

        bool hasEvent();
        const Event& getEvent();

        void consumeEvent();
        void skipEvent();

        void resetPosition();

    private:
        void moveNext();

        bool m_realtimeMouseConsumed;
        bool m_realtimeKeyboardConsumed;
        int m_currentEventIndex;

        vector<Event> m_events;
        vector<bool> m_handled;

        Keyboard m_keyboard;
        Mouse m_mouse;
    };
}
}