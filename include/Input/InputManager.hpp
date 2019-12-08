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
#include "Input/InputQueue.hpp"

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
    using sf::Window;
    using std::tuple;

    class
    {
    public:
        typedef std::function<void()> inputHandler_t;
        typedef std::function<void(Event)> eventHandler_t;

        void processInput(InputQueue& inputQueue);
        void processEvent(Event& event);

        void addBinding(Event::EventType eventType, eventHandler_t handler);
        void addBinding(Event::EventType eventType, Keyboard::Key keyClassifier, eventHandler_t handler);
        void addBinding(Event::EventType eventType, Mouse::Button buttonClassifier, eventHandler_t handler);

        void removeBinding(Event::EventType eventType);
        void removeBinding(Event::EventType eventType, Keyboard::Key keyClassifier);
        void removeBinding(Event::EventType eventType, Mouse::Button buttonClassifier);

        void addRealtimeBinding(Keyboard::Key key, inputHandler_t handler);
        void addRealtimeBinding(Mouse::Button button, inputHandler_t handler);

        void removeRealtimeBinding(Keyboard::Key key);
        void removeRealtimeBinding(Mouse::Button button);

        void clear();

    private:
        std::multimap<Keyboard::Key, inputHandler_t> m_realtimeKeyboardBindings;
        std::multimap<Mouse::Button, inputHandler_t> m_realtimeMouseBindings;
        std::vector<tuple<Event::EventType, int, eventHandler_t>> m_eventBindings;

        void add(Event::EventType type, int classifier, eventHandler_t handler);
        void remove(Event::EventType type, int classifier);
        bool processEvent(Event& event);
    };
}
}