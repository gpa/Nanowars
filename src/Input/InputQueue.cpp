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

    InputQueue::InputQueue(Window& inputSource)
        : m_inputSource(inputSource)
        , m_hasEvent(false)
        , m_realtimeKeyboardConsumed(false)
        , m_realtimeMouseConsumed(false)
    {
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
        if (!m_hasEvent)
            m_hasEvent = m_inputSource.pollEvent(m_currentEvent);

        return m_hasEvent;
    }

    const Event& InputQueue::getEvent()
    {
        if (!hasEvent())
            throw new std::logic_error("No event in the queue.");

        return m_currentEvent;
    }

    void InputQueue::consumeEvent()
    {
        m_hasEvent = false;
    }

    void InputQueue::skipEvent()
    {
        m_skippedEvents.push_back(m_currentEvent);
        m_hasEvent = false;
    }
}
}