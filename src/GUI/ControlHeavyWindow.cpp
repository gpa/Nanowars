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

#include "GUI/ControlHeavyWindow.hpp"

namespace nanowars {
namespace gui {

    ControlHeavyWindow::ControlHeavyWindow(GUIManager& guiManager, AssetHolder&& assetHolder)
        : Window(guiManager, std::move(assetHolder))
    {
    }

    shared_ptr<CheckButton> ControlHeavyWindow::getCheckButton(string id, function<void()> onClick)
    {
        auto cb = CheckButton::Create("");
        cb->SetId(id);
        cb->GetSignal(Widget::OnLeftClick).Connect(onClick);
        m_checkboxes.push_back(cb);
        return cb;
    }

    shared_ptr<ComboBox> ControlHeavyWindow::getComboBox(string id, function<void()> onClick)
    {
        auto cb = ComboBox::Create();
        cb->SetId(id);
        cb->GetSignal(Widget::OnLeftClick).Connect(onClick);
        m_comboboxs.push_back(cb);
        return cb;
    }

    shared_ptr<Entry> ControlHeavyWindow::getEntry(string id, function<void()> onClick)
    {
        auto e = Entry::Create();
        e->SetId(id);
        e->GetSignal(Widget::OnText).Connect(onClick);
        m_entries.push_back(e);
        return e;
    }

    shared_ptr<Button> ControlHeavyWindow::getButton(string id, string label, function<void()> onClick)
    {
        auto b = Button::Create(label);
        b->SetId(id);
        b->GetSignal(Widget::OnLeftClick).Connect(onClick);
        m_buttons.push_back(b);
        return b;
    }

    shared_ptr<Scale> ControlHeavyWindow::getScale(string id, function<void()> onClick)
    {
        auto a = Scale::Create(Scale::Orientation::HORIZONTAL);
        a->SetId(id);
        a->GetSignal(Widget::OnLeftClick).Connect(onClick);
        m_scales.push_back(a);
        auto scrollbar = Scrollbar::Create(Scrollbar::Orientation::VERTICAL);
        auto range = scrollbar->GetAdjustment();
        range->SetLower(0.f);
        range->SetUpper(100.f);
        range->SetMinorStep(3.f);
        range->SetMajorStep(12.f);
        a->SetAdjustment(range);
        return a;
    }

    void ControlHeavyWindow::insertLabelRow(string label, shared_ptr<Table> table, int posX, int posY, int width, int height)
    {
        table->Attach(Label::Create(label), Rect<Uint32>(posX, posY, width, height), Table::FILL, Table::FILL, sf::Vector2f(10.f, 10.f));
    }

    shared_ptr<ComboBox> ControlHeavyWindow::addCombo(shared_ptr<Table> table, function<void()> onClick, string id, string label,
        int lX, int lY, int objX, int objY, int offX, int offY)
    {
        auto obj = getComboBox(id, onClick);
        insertLabelRow(label, table, lX, lY);
        if (offX != -1)
            insertRow(obj, table, objX, objY, offX, offY);
        else
            insertRow(obj, table, objX, objY);
        return obj;
    }

    shared_ptr<CheckButton> ControlHeavyWindow::addCheckbox(shared_ptr<Table> table, function<void()> onClick, string id, string label,
        int lX, int lY, int objX, int objY, int offX, int offY)
    {
        auto obj = getCheckButton(id, onClick);
        insertLabelRow(label, table, lX, lY);
        if (offX != -1)
            insertRow(obj, table, objX, objY, offX, offY);
        else
            insertRow(obj, table, objX, objY);
        return obj;
    }

    shared_ptr<Button> ControlHeavyWindow::getButtonById(string id)
    {
        for (auto& btn : m_buttons)
        {
            if (btn->GetId() == id)
            {
                return btn;
            }
        }

        return shared_ptr<Button>();
    }
}
}