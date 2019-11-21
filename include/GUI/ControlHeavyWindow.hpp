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

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widget.hpp>

#include "GUI/Window.hpp"
#include "GUI/GUIManager.hpp"

#include <memory>
#include <vector>
#include <functional>

namespace nanowars {
namespace gui {

    using std::vector;
    using std::shared_ptr;
    using std::function;
    using namespace sfg;

    class ControlHeavyWindow : public Window
    {
    public:
        ControlHeavyWindow(GUIManager& guiManager, AssetHolder&& assetHolder);
        
    protected:
        shared_ptr<CheckButton> getCheckButton(string id, function<void()> onClick);
        shared_ptr<ComboBox> getComboBox(string id, function<void()> onClick);
        shared_ptr<Entry> getEntry(string id, function<void()> onClick);
        shared_ptr<Scale> getScale(string id, function<void()> onClick);
        shared_ptr<Button> getButton(string id, string label, function<void()> onClick);

        shared_ptr<ComboBox> addCombo(shared_ptr<Table> table, function<void()> onClick,
            string id, string label, int lX, int lY, int objX, int objY, int offX = -1, int offY = -1);
        shared_ptr<CheckButton> addCheckbox(shared_ptr<Table> table, function<void()> onClick, string id,
            string label, int lX, int lY, int objX, int objY, int offX = -1, int offY = -1);

        void insertLabelRow(string label, shared_ptr<Table> table, int posX, int posY, int width = 1, int height = 1);
        template <typename T>
        void insertRow(T obj, shared_ptr<Table> table, int posX, int posY, int width = 1, int height = 1);

        shared_ptr<Button> getButtonById(string id);

        vector<shared_ptr<CheckButton>> m_checkboxes;
        vector<shared_ptr<Button>> m_buttons;
        vector<shared_ptr<ComboBox>> m_comboboxs;
        vector<shared_ptr<Entry>> m_entries;
        vector<shared_ptr<Scale>> m_scales;
    };

    template <typename T>
    inline void ControlHeavyWindow::insertRow(T obj, shared_ptr<Table> table, int posX, int posY, int width, int height)
    {
        table->Attach(obj, Rect<Uint32>(posX, posY, width, height), Table::FILL, Table::FILL, sf::Vector2f(10.f, 10.f));
    }
}
}