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

    class ConfirmationWindow : public Window
    {
    public:
        ConfirmationWindow(GUIManager& guiManager, AssetHolder&& assetHolder,
            string infoText, string acceptString, string rejectString, string windowTitle, float rejectXOffset = 0.0f);

        void update(float dt) override;

        bool isRejected() const;
        bool isAccepted() const;

    private:
        bool m_accepted;
        bool m_rejected;

        void onAccepted();
        void onRejected();
    };
}
}
