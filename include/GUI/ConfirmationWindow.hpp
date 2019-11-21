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
#include <string>

namespace nanowars {
namespace gui {

    using std::string;

    class ConfirmationWindow : public Window
    {
    public:
        ConfirmationWindow(GUIManager& guiManager, AssetHolder&& assetHolder, 
            string titleString, string infoString, string acceptString, string rejectString);
        
        void initialize() override;

        bool isRejected() const;
        bool isAccepted() const;
    private:
        string m_titleString;
        string m_infoString;
        string m_acceptString;
        string m_rejectString;

        bool m_accepted;
        bool m_rejected;

        void onAccepted();
        void onRejected();
    };
}
}
