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

#include "Input/InputQueue.hpp"

namespace nanowars {
namespace input {

    InputQueue::InputQueue()
        : m_currentEventIndex(0)
        , m_realtimeKeyboardConsumed(false)
        , m_realtimeMouseConsumed(false)
    {
        m_events.reserve(15);
        m_handled.reserve(15);
    }

    void InputQueue::consume(Window& window)
    {
        m_realtimeKeyboardConsumed = false;
        m_realtimeMouseConsumed = false;
        m_currentEventIndex = 0;
        m_events.clear();
        m_handled.clear();

        Event event;
        while (window.pollEvent(event))
        {
            m_events.push_back(event);
            m_handled.push_back(false);
        }
    }

    void InputQueue::resetPosition()
    {
        m_currentEventIndex = 0;
    }

    bool InputQueue::canConsumeRealtimeMouseInput()
    {
        return !m_realtimeMouseConsumed;
    }

    sf::Mouse& InputQueue::consumeRealtimeMouseInput()
    {
        if (m_realtimeMouseConsumed)
            throw std::logic_error("The realtime mouse input has been already consumed.");

        m_realtimeMouseConsumed = true;
        return m_mouse;
    }

    bool InputQueue::canConsumeRealtimeKeyboardInput()
    {
        return !m_realtimeKeyboardConsumed;
    }

    sf::Keyboard& InputQueue::consumeRealtimeKeyboardInput()
    {
        if (m_realtimeKeyboardConsumed)
            throw std::logic_error("The realtime keyboard input has been already consumed.");

        m_realtimeKeyboardConsumed = true;
        return m_keyboard;
    }

    bool InputQueue::hasEvent()
    {
        return m_currentEventIndex < m_events.size();
    }

    const Event& InputQueue::getEvent()
    {
        if (!hasEvent())
            throw new std::logic_error("No event in the queue.");

        return m_events[m_currentEventIndex];
    }

    void InputQueue::consumeEvent()
    {
        m_handled[m_currentEventIndex] = true;
        moveNext();
    }

    void InputQueue::skipEvent()
    {
        m_handled[m_currentEventIndex] = false;
        moveNext();
    }

    void InputQueue::moveNext()
    {
        m_currentEventIndex++;
        while (m_currentEventIndex < m_events.size() && m_handled[m_currentEventIndex])
            m_currentEventIndex++;
    }
}
}