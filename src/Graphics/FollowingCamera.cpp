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

#include "Graphics/FollowingCamera.hpp"
#include "Core/Constants.hpp"

namespace nanowars {
namespace graphics {

    FollowingCamera::FollowingCamera(float startZoom)
    {
        m_view.zoom(startZoom);
        m_followedEntity = nullptr;
    }

    void FollowingCamera::follow(Entity* entity)
    {
        m_followedEntity = entity;
        m_followedController = nullptr;
    }

    void FollowingCamera::follow(EntityController* controller)
    {
        m_followedController = controller;
        m_followedEntity = nullptr;
    }

    const View& FollowingCamera::getView() const
    {
        auto* entity = m_followedEntity;
        if (entity == nullptr && m_followedController != nullptr)
            entity = m_followedController->getEntity();

        if (entity != nullptr)
        {
            auto position = entity->getBody().GetPosition();
            m_view.setCenter(position.x * core::constants::meterToPixelRatio, position.y * core::constants::meterToPixelRatio);
        }

        return m_view;
    }
}
}