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

#define BOOST_GEOMETRY_OVERLAY_NO_THROW
#define BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE

#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/geometry.hpp>

#include "Math/Vector2.hpp"

BOOST_GEOMETRY_REGISTER_POINT_2D(nanowars::math::Vector2f,
    float,
    boost::geometry::cs::cartesian,
    x,
    y)