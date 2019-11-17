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

#include "Core/GameLoopParticipant.hpp"
#include "Asset/AssetHolder.hpp"
#include "GUI/Window.hpp"

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <stack>
#include <memory>

namespace nanowars {
namespace core {
    class Application;
}
}

namespace nanowars {
namespace gui {

    using namespace asset;
    using namespace gui;
    using namespace std;
    using namespace core;

    class GUIManager : public GameLoopParticipant
    {
    public:
        GUIManager(Application& application, AssetHolder&& assetHolder);

        void initializeWindows();

        void update(float dt) override;
        void render(RenderWindow& window) override;

        bool handleEvent(const Event& event) override;
        bool handleContinuousEvent(const Mouse& mouse, const Keyboard& keyboard) override;

        Application& getApplication() const;

        void makeTopMost(shared_ptr<Window> window);
        void removeTopMost();

    private:
        sfg::SFGUI m_sfgui;
        sfg::Desktop m_desktop;
        Application& m_application;

        AssetHolder m_assetHolder;
        stack<shared_ptr<Window>> m_windows;
    };
}
}