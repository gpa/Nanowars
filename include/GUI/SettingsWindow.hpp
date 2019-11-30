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

#include "GUI/ControlHeavyWindow.hpp"
#include "Globalization/StringTranslations.hpp"
#include "Globalization/TranslationManager.hpp"

namespace nanowars {
namespace gui {

    using namespace sfg;
    using namespace globalization;
    using std::shared_ptr;

    class SettingsWindow : public FixedPositionWindow, protected ControlHeavyWindow
    {
    public:
        SettingsWindow(GUIManager& guiManager, AssetHolder&& assetHolder);

        void HandleEvent(const Event& event) override;
    protected:
        void initialize() override;

    private:
        void initControls();
        void initGraphicsTab(shared_ptr<Box>);
        void initAudioTab(shared_ptr<Box>);
        void initControlsTab(shared_ptr<Box>);
        void initNetworkTab(shared_ptr<Box>);

        void initScreenResolutionOptions(shared_ptr<ComboBox>);
        void initAntiAliasingOptions(shared_ptr<ComboBox>);

        void loadConfigState();
        void saveConfigState();

        void onCloseButtonClicked();
        void onApplyButtonClicked();
        void onRestoreButtonClicked();

        void enterControlKeyInputMode();
        bool isControlKeyInputMode();
        void handleEventInInputMode(const Event& event);

        void onRestoreDefaultsConfirmation(bool wasConfirmed);
        void onSaveChangesConfirmation(bool wasConfirmed);

        bool m_graphicsModified;
        bool m_audioModified;
        bool m_controlsModified;
        bool m_networkModified;

        string m_keyBindingButtonId;
    };
}
}