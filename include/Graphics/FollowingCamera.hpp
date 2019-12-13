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
#include "Gameplay/Entity.hpp"
#include "Gameplay/Controllers/EntityController.hpp"
#include "Graphics/Camera.hpp"
#include <SFML/Graphics/View.hpp>

namespace nanowars {
namespace graphics {

    using namespace gameplay;
    using namespace controllers;

    class FollowingCamera : public Camera
    {
    public:
        FollowingCamera(float startZoom);
        
        void follow(Entity* Entity);
        void follow(EntityController* entityController);
        
        virtual const View& getView() const override;

    private:
        Entity* m_followedEntity;
        EntityController* m_followedController;
    };
}
}