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

#include <Controllers/RocketController.hpp>

namespace nanowars {
namespace controllers {

    RocketController::RocketController()
    {
        m_controlledRocket = nullptr;
	}

    void RocketController::setRocket(Rocket* rocket)
    {
        m_controlledRocket = rocket;
    }

    void RocketController::fly()
    {
        if (m_controlledRocket == nullptr)
            return;
        m_controlledRocket->applyMainThrust();
    }

    void RocketController::flyLeft()
    {
        if (m_controlledRocket == nullptr)
            return;
        m_controlledRocket->applyRightThrust();
    }

    void RocketController::flyRight()
    {
        if (m_controlledRocket == nullptr)
            return;
        m_controlledRocket->applyLeftThrust();
    }

    void RocketController::shoot()
    {
        if (m_controlledRocket == nullptr)
            return;
        m_controlledRocket->shoot();
    }
}
}