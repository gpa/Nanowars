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

#include "Graphics/FreeCamera.hpp"

#include <SFML/Window/Event.hpp>

namespace nanowars {
namespace graphics {

    FreeCamera::FreeCamera()
    {
        zoom(10.f);
        m_isNavigationInProgress = false;
    }

    void FreeCamera::zoom(float f)
    {
        float factor = f > 0.f ? 0.9f : 1.1f;
        m_view.zoom(f);
    }

    void FreeCamera::move(float dx, float dy)
    {
        m_view.move(dx, dy);
    }

    bool FreeCamera::handleEvent(const sf::Event& event)
    {
        switch (event.type)
        {
        case sf::Event::MouseButtonPressed: {
            if (event.mouseButton.button == sf::Mouse::Button::Middle)
            {
                m_lastMousePos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
                m_isNavigationInProgress = true;
            }
        }
        break;
        case sf::Event::MouseButtonReleased: {
            m_isNavigationInProgress = false;
        }
        break;
        case sf::Event::MouseWheelMoved: {
            float factor = event.mouseWheel.delta > 0.f ? 0.9f : 1.1f;
            m_mouseSensitivity += event.mouseWheel.delta < 0 ? 0.2f : -0.2f;
            m_mouseSensitivity = std::max(1.0f, m_mouseSensitivity);
            m_view.zoom(factor);
        }
        break;
        case sf::Event::MouseMoved: {
            if (m_isNavigationInProgress)
            {
                float linearMouseSensitivity = 20.0f;
                auto newPos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
                auto delta = (m_lastMousePos - newPos);
                m_view.move((float)(delta.x * linearMouseSensitivity), (float)(delta.y * linearMouseSensitivity));
                m_lastMousePos = newPos;
            }
        }
        break;
        default:
            return false;
        }

        return true;
    }
}
}
