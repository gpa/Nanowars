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

#include "Input/InputManager.hpp"
#include <SFML/Window/Window.hpp>
#include <algorithm>

namespace nanowars {
namespace input {

    void InputManager::addRealtimeBinding(sf::Keyboard::Key key, inputHandler_t handler)
    {
        m_realtimeKeyboardBindings.insert(std::make_pair(key, handler));
    }

    void InputManager::addRealtimeBinding(sf::Mouse::Button button, inputHandler_t handler)
    {
        m_realtimeMouseBindings.insert(std::make_pair(button, handler));
    }

    void InputManager::removeRealtimeBinding(sf::Keyboard::Key key)
    {
        m_realtimeKeyboardBindings.erase(key);
    }

    void InputManager::removeRealtimeBinding(sf::Mouse::Button button)
    {
        m_realtimeMouseBindings.erase(button);
    }

    void InputManager::addBinding(Event::EventType eventType, eventHandler_t handler)
    {
        add(eventType, -1, handler);
    }

    void InputManager::addBinding(Event::EventType eventType, Keyboard::Key keyClassifier, eventHandler_t handler)
    {
        if (eventType != Event::EventType::KeyPressed && eventType != Event::EventType::KeyReleased)
            throw new std::logic_error("The given event type is not valid for this method.");

        add(eventType, static_cast<int>(keyClassifier), handler);
    }

    void InputManager::addBinding(Event::EventType eventType, Mouse::Button buttonClassifier, eventHandler_t handler)
    {
        if (eventType != Event::EventType::MouseButtonPressed && eventType != Event::EventType::MouseButtonReleased)
            throw new std::logic_error("The given event type is not valid for this method.");

        add(eventType, static_cast<int>(buttonClassifier), handler);
    }

    void InputManager::removeBinding(Event::EventType eventType)
    {
        remove(eventType, -1);
    }

    void InputManager::removeBinding(Event::EventType eventType, Keyboard::Key keyClassifier)
    {
        remove(eventType, static_cast<int>(keyClassifier));
    }

    void InputManager::removeBinding(Event::EventType eventType, Mouse::Button buttonClassifier)
    {
        remove(eventType, static_cast<int>(buttonClassifier));
    }

    void InputManager::add(Event::EventType eventType, int classifier, eventHandler_t handler)
    {
        m_eventBindings.push_back(std::make_tuple(eventType, classifier, handler));
    }

    void InputManager::remove(Event::EventType eventType, int classifier)
    {
        for (size_t i = 0; i < m_eventBindings.size(); ++i)
        {
            if (std::get<0>(m_eventBindings[i]) == eventType && std::get<1>(m_eventBindings[i]) == classifier)
            {
                m_eventBindings.erase(m_eventBindings.begin() + i);
                i--;
            }
        }
    }

    void InputManager::processEvent(Event& event)
    {
        triggerEvent(event);
    }

    void InputManager::processInput(InputQueue& inputQueue)
    {
        if (inputQueue.canConsumeRealtimeMouseInput() && m_realtimeMouseBindings.size() != 0)
        {
            auto& mouse = inputQueue.consumeRealtimeMouseInput();
            for (const auto& inputBinding : m_realtimeMouseBindings)
                if (mouse.isButtonPressed(inputBinding.first))
                    inputBinding.second();
        }

        if (inputQueue.canConsumeRealtimeKeyboardInput() && m_realtimeKeyboardBindings.size() != 0)
        {
            auto& keyboard = inputQueue.consumeRealtimeKeyboardInput();
            for (const auto& inputBinding : m_realtimeKeyboardBindings)
                if (keyboard.isKeyPressed(inputBinding.first))
                    inputBinding.second();
        }

        while (inputQueue.hasEvent())
        {
            Event event = inputQueue.getEvent();
            if (triggerEvent(event))
                inputQueue.consumeEvent();
            else
                inputQueue.skipEvent();
        }
    }

    bool InputManager::triggerEvent(Event& event)
    {
        bool handled = false;
        for (const auto& binding : m_eventBindings)
        {
            auto type = std::get<0>(binding);
            auto classifier = std::get<1>(binding);
            auto handler = std::get<2>(binding);

            if (event.type == type)
            {
                if (classifier == -1)
                {
                    handler(event);
                    handled = true;
                }
                else
                {
                    if (event.type == Event::EventType::KeyPressed || event.type == Event::EventType::KeyReleased)
                    {
                        if (static_cast<int>(event.key.code) == classifier)
                        {
                            handler(event);
                            handled = true;
                        }
                    }
                    else if (event.type == Event::EventType::MouseButtonPressed || event.type == Event::EventType::MouseButtonReleased)
                    {
                        if (static_cast<int>(event.mouseButton.button) == classifier)
                        {
                            handler(event);
                            handled = true;
                        }
                    }
                }
            }
        }

        return handled;
    }

    void InputManager::clear()
    {
        m_realtimeKeyboardBindings.clear();
        m_realtimeMouseBindings.clear();
        m_eventBindings.clear();
    }
}
}