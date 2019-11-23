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

#include "GUI/SettingsWindow.hpp"
#include "GUI/GUIManager.hpp"
#include "GUI/ConfirmationWindow.hpp"
#include "Config/ConfigManager.hpp"
#include "Config/ConfigEntry.hpp"
#include "Config/UserConfiguration.hpp"

#include "Core/Application.hpp"
#include "Core/ApplicationInitializer.hpp"

#include <functional>
#include <Thor/Input.hpp>
#include <SFML/Graphics.hpp>

namespace nanowars {
namespace gui {

    using namespace sf;
    using namespace nanowars::config;
    using configEntry_t = ConfigEntry::configEntry_t;
    using ConfEntry = nanowars::config::ConfigEntry;

    SettingsWindow::SettingsWindow(GUIManager& guiManager, AssetHolder&& assetHolder)
        : FixedPositionWindow(guiManager, std::move(assetHolder))
    {
    }

    void SettingsWindow::initialize()
    {
        SetTitle(tx(StringTranslation_NanowarsSettings));
        SetStyle(sfg::Window::Style::BACKGROUND | sfg::Window::Style::TITLEBAR | sfg::Window::Style::CLOSE);
        GetSignal(sfg::Window::OnCloseButton).Connect(std::bind(&SettingsWindow::onCloseButtonClicked, this));

        m_graphicsModified = m_audioModified = m_controlsModified = m_networkModified = false;

        initControls();
        loadConfigState();
        setFixedPosition(FixedPosition::CenterVertically | FixedPosition::CenterHorizontally);
        FixedPositionWindow::initialize();
    }

    void SettingsWindow::initControls()
    {
        auto winBox = Box::Create(Box::Orientation::VERTICAL);
        auto graphicsBox = Box::Create(Box::Orientation::VERTICAL);
        auto audioBox = Box::Create(Box::Orientation::VERTICAL);
        auto controlsBox = Box::Create(Box::Orientation::VERTICAL);
        auto networkBox = Box::Create(Box::Orientation::VERTICAL);
        auto notebook = Notebook::Create();

        initGraphicsTab(graphicsBox);
        initAudioTab(audioBox);
        initControlsTab(controlsBox);
        initNetworkTab(networkBox);

        notebook->AppendPage(graphicsBox, Label::Create(tx(StringTranslation_Graphics)));
        notebook->AppendPage(audioBox, Label::Create(tx(StringTranslation_Audio)));
        notebook->AppendPage(controlsBox, Label::Create(tx(StringTranslation_Controls)));
        notebook->AppendPage(networkBox, Label::Create(tx(StringTranslation_Network)));

        winBox->Pack(notebook);

        auto applyButton = Button::Create(tx(StringTranslation_ApplyChanges));
        auto restoreButton = Button::Create(tx(StringTranslation_RestoreDefaults));

        applyButton->GetSignal(Widget::OnLeftClick).Connect(std::bind(&SettingsWindow::onApplyButtonClicked, this));
        restoreButton->GetSignal(Widget::OnLeftClick).Connect(std::bind(&SettingsWindow::onRestoreButtonClicked, this));

        auto fixed = Fixed::Create();
        fixed->Put(applyButton, sf::Vector2f(800.f, 10.f));
        fixed->Put(restoreButton, sf::Vector2f(680, 10.0f));

        winBox->Pack(fixed, false, true);
        Add(winBox);
    }

    void SettingsWindow::initGraphicsTab(shared_ptr<Box> box)
    {
        auto table = Table::Create();
        auto onModify = [&]() { m_graphicsModified = true; };

        auto resolutionCombo = addCombo(table, onModify, userConfiguration::graphics::resolution,
            tx(StringTranslation_ScreenResolution), 0, 0, 1, 0, 3, 1);

        auto fullscreenCheckbox = addCheckbox(table, onModify, userConfiguration::graphics::fullscreen,
            tx(StringTranslation_FullScreen), 0, 1, 1, 1);

        auto vsyncCheckbox = addCheckbox(table, onModify, userConfiguration::graphics::vsync,
            tx(StringTranslation_VSync), 0, 2, 1, 2);

        auto antiAliasingCombo = addCombo(table, onModify, userConfiguration::graphics::antiAliasing,
            tx(StringTranslation_AntiAliasing), 0, 3, 1, 3);

        auto showFpsCheckbox = addCheckbox(table, onModify, userConfiguration::graphics::showFps,
            tx(StringTranslation_ShowFps), 0, 4, 1, 4);

        initScreenResolutionOptions(resolutionCombo);
        initAntiAliasingOptions(antiAliasingCombo);

        box->Pack(table);
    }

    void SettingsWindow::initAudioTab(shared_ptr<Box> box)
    {
        auto table = Table::Create();
        auto onModify = [&]() { m_audioModified = true; };

        insertLabelRow(tx(StringTranslation_MenuSoundEffects), table, 0, 0);
        insertRow(getScale(userConfiguration::audio::menuEffects, onModify), table, 1, 0, 11);

        insertLabelRow(tx(StringTranslation_GameSoundEffects), table, 0, 1);
        insertRow(getScale(userConfiguration::audio::gameEffects, onModify), table, 1, 1, 11);

        insertLabelRow(tx(StringTranslation_MenuMusic), table, 0, 2);
        insertRow(getScale(userConfiguration::audio::menuMusic, onModify), table, 1, 2, 11);

        insertLabelRow(tx(StringTranslation_GameMusic), table, 0, 3);
        insertRow(getScale(userConfiguration::audio::gameMusic, onModify), table, 1, 3, 11);

        box->Pack(table);
    }

    void SettingsWindow::initControlsTab(shared_ptr<Box> box)
    {
        auto table = Table::Create();

        auto addRow = [&](string id, int x, int y, int ox, int oy) {
            insertRow(getButton(id, "-", [this, id]() { m_keyBindingButtonId = id; enterControlKeyInputMode(); }), table, x, y, ox, oy);
        };

        insertLabelRow("", table, 0, 0);
        insertLabelRow(tx(StringTranslation_Main), table, 1, 0, 10, 1);
        insertLabelRow(tx(StringTranslation_Alternative), table, 11, 0, 10, 1);

        insertLabelRow(tx(StringTranslation_Thrust), table, 0, 1);
        addRow(userConfiguration::controls::mainThrust, 1, 1, 10, 1);
        addRow(userConfiguration::controls::altThrust, 11, 1, 10, 1);

        insertLabelRow(tx(StringTranslation_Left), table, 0, 2);
        addRow(userConfiguration::controls::mainLeft, 1, 2, 10, 1);
        addRow(userConfiguration::controls::altLeft, 11, 2, 10, 1);

        insertLabelRow(tx(StringTranslation_Right), table, 0, 3);
        addRow(userConfiguration::controls::mainRight, 1, 3, 10, 1);
        addRow(userConfiguration::controls::altRight, 11, 3, 10, 1);

        insertLabelRow(tx(StringTranslation_Shoot), table, 0, 4);
        addRow(userConfiguration::controls::mainShoot, 1, 4, 10, 1);
        addRow(userConfiguration::controls::altShoot, 11, 4, 10, 1);

        insertLabelRow(tx(StringTranslation_Chat), table, 0, 5);
        addRow(userConfiguration::controls::mainChat, 1, 5, 10, 1);
        addRow(userConfiguration::controls::altChat, 11, 5, 10, 1);

        box->Pack(table);
    }

    void SettingsWindow::initNetworkTab(shared_ptr<Box> box)
    {
        auto table = Table::Create();
        auto onModify = [&]() { m_audioModified = true; };

        auto nameEntry = getEntry(userConfiguration::network::name, onModify);
        insertLabelRow(tx(StringTranslation_NetworkName), table, 0, 0);
        insertRow(nameEntry, table, 1, 0, 11, 1);

        box->Pack(table);
    }

    void SettingsWindow::initScreenResolutionOptions(shared_ptr<ComboBox> combobox)
    {
        for (const auto& res : VideoMode::getFullscreenModes())
        {
            if (res.bitsPerPixel == 8)
            {
                auto resolution = std::to_string(res.width) + "x" + std::to_string(res.height);
                combobox->AppendItem(resolution);
            }
        }
    }

    void SettingsWindow::initAntiAliasingOptions(shared_ptr<ComboBox> combobox)
    {
        for (int i = 0; i <= 8; ++i)
            combobox->AppendItem(std::to_string(i));
    }

    void SettingsWindow::HandleEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::KeyReleased && isControlKeyInputMode())
            handleEventInInputMode(event);

        FixedPositionWindow::HandleEvent(event);
    }

    void SettingsWindow::handleEventInInputMode(const Event& event)
    {
        if (event.key.code == sf::Keyboard::Key::Escape)
        {
            auto button = getButtonById(m_keyBindingButtonId);
            if (button.get() != nullptr)
                button->SetLabel(m_guiManager.getConfigManager().getString(button->GetId()));

            m_keyBindingButtonId.clear();
            return;
        }

        if (event.key.code == sf::Keyboard::Key::Unknown)
            return;

        string keyAsString = thor::toString(event.key.code);
        auto button = getButtonById(m_keyBindingButtonId);

        if (button.get() != nullptr)
        {
            button->SetLabel(keyAsString);
            m_keyBindingButtonId.clear();
        }
    }

    void SettingsWindow::enterControlKeyInputMode()
    {
        auto button = getButtonById(m_keyBindingButtonId);

        if (button.get() != nullptr)
        {
            button->SetLabel(tx(StringTranslation_PressKey));
        }
    }

    void SettingsWindow::loadConfigState()
    {
        auto& conf = m_guiManager.getConfigManager();
        for (auto& cb : m_checkboxes)
            cb->SetActive(conf.getBool(cb->GetId()));

        for (auto& btn : m_buttons)
            btn->SetLabel(conf.getString(btn->GetId()));

        for (auto& scale : m_scales)
            scale->GetAdjustment()->SetValue(conf.getFloat(scale->GetId()));

        for (auto& entry : m_entries)
            entry->SetText(conf.getString(entry->GetId()));

        for (auto& combo : m_comboboxes)
        {
            auto id = combo->GetId();

            if (id == userConfiguration::graphics::resolution)
            {
                auto res = conf.getString(userConfiguration::graphics::resolution);
                int index = 0;
                for (int i = 0; i < combo->GetItemCount(); ++i)
                {
                    if (combo->GetItem(i) == res)
                    {
                        index = i;
                        break;
                    }
                }
                combo->SelectItem(index);
            }
            else if (id == userConfiguration::graphics::antiAliasing)
                combo->SelectItem(conf.getInt(userConfiguration::graphics::antiAliasing));
        }
    }

    void SettingsWindow::saveConfigState()
    {
        auto& conf = m_guiManager.getConfigManager();
        for (auto& cb : m_checkboxes)
            conf.setEntry(ConfEntry(cb->GetId(), configEntry_t(cb->IsActive())));

        for (auto& btn : m_buttons)
            conf.setEntry(ConfEntry(btn->GetId(), configEntry_t(btn->GetLabel())));

        for (auto& scale : m_scales)
            conf.setEntry(ConfEntry(scale->GetId(), configEntry_t(scale->GetAdjustment()->GetValue())));

        for (auto& entry : m_entries)
            conf.setEntry(ConfEntry(entry->GetId(), configEntry_t(entry->GetText())));

        for (auto& combo : m_comboboxes)
        {
            auto id = combo->GetId();

            if (id == userConfiguration::graphics::resolution)
                conf.setEntry(ConfEntry(id, configEntry_t(combo->GetSelectedText())));
            else if (id == userConfiguration::graphics::antiAliasing)
            {
                string s = combo->GetSelectedText();
                conf.setEntry(ConfEntry(id, configEntry_t(std::stoi(s.c_str()))));
            }
        }

        conf.save();
    }

    void SettingsWindow::onCloseButtonClicked()
    {
        if(!(m_graphicsModified || m_audioModified || m_controlsModified || m_networkModified))
        {
            m_guiManager.removeTopMost();
            return;
        }

        auto confirmationWindow = std::make_shared<ConfirmationWindow>(m_guiManager, m_assetHolder.getNewHolder(),
            tx(StringTranslation_UnsavedChanges),
            tx(StringTranslation_ApplyMadeChanges),
            tx(StringTranslation_ApplyChanges),
            tx(StringTranslation_DiscardChanges),
            std::bind(&SettingsWindow::onDiscardChangesConfirmation, this, std::placeholders::_1));
        confirmationWindow->initialize();

        m_guiManager.makeTopMost(confirmationWindow);
    }

    void SettingsWindow::onApplyButtonClicked()
    {
        saveConfigState();
        m_keyBindingButtonId.clear();

        if (m_graphicsModified)
        {
            ApplicationInitializer initializer;
            initializer.initWindow(m_guiManager.getWindow(), m_guiManager.getConfigManager());
        }

        m_graphicsModified = m_audioModified = m_controlsModified = m_networkModified = false;
    }

    void SettingsWindow::onRestoreButtonClicked()
    {
        auto confirmationWindow = std::make_shared<ConfirmationWindow>(m_guiManager, m_assetHolder.getNewHolder(),
            tx(StringTranslation_RestoreDefaults),
            tx(StringTranslation_ResetAllValuesToDefault),
            tx(StringTranslation_RestoreDefaults),
            tx(StringTranslation_Cancel),
            std::bind(&SettingsWindow::onRestoreDefaultsConfirmation, this, std::placeholders::_1));
        confirmationWindow->initialize();

        m_guiManager.makeTopMost(confirmationWindow);
    }

    bool SettingsWindow::isControlKeyInputMode()
    {
        return !m_keyBindingButtonId.empty();
    }

    void SettingsWindow::onRestoreDefaultsConfirmation(bool wasConfirmed)
    {

    }

    void SettingsWindow::onDiscardChangesConfirmation(bool wasConfirmed)
    {
        if (wasConfirmed)
            m_guiManager.removeTopMost();
    }
}
}