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

#include "GUI/FixedPositionWindow.hpp"
#include <string>

#include <functional>

namespace nanowars {
namespace gui {

    using std::string;
    using std::string;

    class ConfirmationWindow : public FixedPositionWindow
    {
    public:
        typedef function<void(bool)> callback_t;

        ConfirmationWindow(GUIManager& guiManager, AssetHolder&& assetHolder,
            string titleString, string infoString, string acceptString, string rejectString, callback_t callback);

        void HandleEvent(const sf::Event& event) override;

    protected:
        void initialize() override;

    private:
        string m_titleString;
        string m_infoString;
        string m_acceptString;
        string m_rejectString;
        callback_t m_callback;

        void onAccepted();
        void onRejected();
    };
}
}
