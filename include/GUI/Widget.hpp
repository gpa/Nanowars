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

#include <string>
#include <memory>

#include <SFML/Config.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Drawable.hpp>

namespace nanowars {
namespace gui {

    using std::string;
    using sf::Drawable;
    using std::weak_ptr;
    using std::shared_ptr;
    using sf::Keyboard;
    using sf::Uint32;

    class ContainerWidget;
    class Widget : public Drawable
    {
    public:
        inline string getId() const;
        inline void setId(string id);

        inline string getClass() const;
        inline void setClass(string widgetClass);

        inline weak_ptr<ContainerWidget> getParent();
        inline void setParent(weak_ptr<ContainerWidget> parent);

        virtual void handleResize(int width, int height);
        virtual void handleReposition(int width, int height);
        virtual void handleKey(Keyboard::Key key);
        virtual void handleEnteredText(Uint32 character);
        virtual void handleMouseEnter(int x, int y);
        virtual void handleMouseMove(int x, int y);
        virtual void handleMouseLeave(int x, int y);
        virtual void handleMouseWheelMove(int x, int y, int delta);
        virtual void handleUpdate(float seconds);
        virtual void handleFocusChange(Widget* focusedWidget);

    private:
        string m_id;
        string m_class;
        weak_ptr<ContainerWidget> m_parent;
    };
}
}