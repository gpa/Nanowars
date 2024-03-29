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
namespace nanowars {
namespace globalization {

    enum class StringTranslation
    {
        // MainMenu
        OnlineGame,
        LanGame,
        LocalGame,
        Settings,
        Exit,
        ExitNanowars,
        Resume,
        ReturnToMainMenu,
        ExitGameAndReturnToMainMenu,
        ExitGameAndReturnToDesktop,
        OK,
        Cancel,

        // Settings
        NanowarsSettings,
        Graphics,
        Audio,
        Controls,
        Network,
        ApplyChanges,
        RestoreDefaults,
        ScreenResolution,
        FullScreen,
        VSync,
        AntiAliasing,
        ShowFps,
        MenuSoundEffects,
        GameSoundEffects,
        MenuMusic,
        GameMusic,
        Main,
        Alternative,
        Thrust,
        Left,
        Right,
        Shoot,
        Chat,
        NetworkName,
        PressKey,
        ResetAllValuesToDefault,
        ApplyMadeChanges,
        DiscardChanges,
        UnsavedChanges,

        // Game
        Player1,
        Player2,
        _StringTranslationCount
    };
}
}