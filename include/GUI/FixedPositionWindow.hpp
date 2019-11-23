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

#include "GUI/Window.hpp"

namespace nanowars {
namespace gui {

    class FixedPositionWindow : public Window
    {
    public:
        FixedPositionWindow(GUIManager& guiManager, AssetHolder&& AssetHolder);

        void HandleUpdate(float dt) override;

    protected:

        enum FixedPosition
        {
            CenterHorizontally = 1,
            CenterVertically = 2,
            StickToTop = 4,
            StickToLeft = 8,
            StickToBottom = 16,
            StickToRight = 32,
            FullWidth = 62,
            FullHeight = 128
        };

        void initialize() override;
        void setFixedPosition(int positionFlags);
        int getFixedPosition();

    private:
        void updatePosition();
        void centerHorizontally();
        void centerVertically();

        int m_positionFlags;
    };
}
}