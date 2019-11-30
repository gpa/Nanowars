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
this program. If not, see <http://www.gnu.org/licenses/>. 
*/
#pragma once
#include "GUI/FixedPositionWindow.hpp"
#include <memory>

namespace nanowars {
namespace gui {

    class MainWindow : public FixedPositionWindow
    {
    public:
        MainWindow(GUIManager& guiManager, AssetHolder&& assetHolder);
        
        void HandleEvent(const Event& event);
        
    protected:
        void initialize() override;
    private:
        void onOnlineButtonClicked();
        void onLanButtonClicked();
        void onLocalButtonClicked();
        void onSettingsButtonClicked();
        void onExitButtonClicked();
        void onResumeButtonClicked();
        void onReturnToMainMenuButtonClicked();

		void onReturnToMainMenuConfirmation(bool confirmed);
        void onExitConfirmation(bool confirmed);

		void exitApplication();
        void exitGame();
    };
}
}