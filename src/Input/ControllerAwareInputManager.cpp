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

#include "Input/ControllerAwareInputManager.hpp"
#include "Input/InputNames.hpp"

namespace nanowars {
namespace input {

    void ControllerAwareInputManager::bindToControllerViaConfiguration(RocketController& rocketController, const ConfigManager& configManager, bool useAlternativeConfig)
    {
        string mainThrust, leftThrust, rightThrust, shoot;

        if (!useAlternativeConfig)
        {
            mainThrust = userConfiguration::controls::mainThrust;
            leftThrust = userConfiguration::controls::mainLeft;
            rightThrust = userConfiguration::controls::mainRight;
            shoot = userConfiguration::controls::mainShoot;
        }
        else
        {
            mainThrust = userConfiguration::controls::altThrust;
            leftThrust = userConfiguration::controls::altLeft;
            rightThrust = userConfiguration::controls::altRight;
            shoot = userConfiguration::controls::altShoot;
        }

        auto mainThrustKey = InputNames::toKey(configManager.getString(mainThrust));
        auto leftThrustKey = InputNames::toKey(configManager.getString(leftThrust));
        auto rightThrustKey = InputNames::toKey(configManager.getString(rightThrust));
        auto shootKey = InputNames::toKey(configManager.getString(shoot));

        addRealtimeBinding(mainThrustKey, std::bind(&RocketController::fly, rocketController));
        addRealtimeBinding(leftThrustKey, std::bind(&RocketController::flyLeft, rocketController));
        addRealtimeBinding(rightThrustKey, std::bind(&RocketController::flyRight, rocketController));
        addRealtimeBinding(shootKey, std::bind(&RocketController::shoot, rocketController));
    }
}
}