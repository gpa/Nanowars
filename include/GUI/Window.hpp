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

#include "Asset/AssetHolder.hpp"
#include "Globalization/StringTranslations.hpp"

#include <SFGUI/Widgets.hpp>
#include <memory>

namespace nanowars {
namespace gui {

    using namespace asset;
    using namespace sf;
    using namespace globalization;
    using namespace std;

    class GUIManager;

    class Window
    {
    public:
        Window(GUIManager& guiManager, AssetHolder&& assetHolder);
        virtual ~Window() = default;

        virtual void update(float dt);
        virtual void handleEvent(const Event& event);

        virtual void onTopMostGained(shared_ptr<Window> previousTopMost);
        virtual void onTopMostLost(shared_ptr<Window> currentTopMost);

        inline shared_ptr<sfg::Window> getSfgWindow() { return m_window; }

        inline string getId() { return m_id; } 
        inline void setId(string id) { this->m_id = id; }

    protected:
        string m_id;
        GUIManager& m_guiManager;
        AssetHolder m_assetHolder;
        shared_ptr<sfg::Window> m_window;

        void center();
        void centerHorizontally();
        void centerVertically();
        void setMargin(float percentX, float percentY);

        string tx(StringTranslation translationId);
    };
}
}