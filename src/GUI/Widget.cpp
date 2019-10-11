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

#include "GUI/Widget.hpp"

namespace nanowars {
namespace gui {

    inline string Widget::getId() const
    {
        return m_id;
    }

    inline void Widget::setId(string id)
    {
        m_id = id;
    }

    inline string Widget::getClass() const
    {
        return m_class;
    }
    inline void Widget::setClass(string widgetClass)
    {
        m_class = widgetClass;
    }

    inline weak_ptr<ContainerWidget> Widget::getParent()
    {
        return m_parent;
    }

    inline void Widget::setParent(weak_ptr<ContainerWidget> parent)
    {
        m_parent = parent;
    }

    void Widget::handleResize(int width, int height)
    {
    }

    void Widget::handleReposition(int width, int height)
    {
    }

    void Widget::handleKey(Keyboard::Key key)
    {
    }

    void Widget::handleEnteredText(Uint32 character)
    {
    }

    void Widget::handleMouseEnter(int x, int y)
    {
    }

    void Widget::handleMouseMove(int x, int y)
    {
    }

    void Widget::handleMouseLeave(int x, int y)
    {
    }

    void Widget::handleMouseWheelMove(int x, int y, int delta)
    {
    }

    void Widget::handleUpdate(float seconds)
    {
    }

    void Widget::handleFocusChange(Widget* focusedWidget)
    {
    }
}
}