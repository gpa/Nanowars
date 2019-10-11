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
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace nanowars {
namespace screens {

    using sf::RenderWindow;
    using sf::Event;
    using sf::Mouse;
    using sf::Keyboard;

    class Screen
    {
    public:
        virtual ~Screen() = default;
        virtual void update(float dt) = 0;
        virtual bool handleEvent(const Event& event) = 0;
        virtual bool handleContinuousEvent(const Mouse& mouse, const Keyboard& keyboard) = 0;
        virtual void render(RenderWindow& window) = 0;
    };
}
}