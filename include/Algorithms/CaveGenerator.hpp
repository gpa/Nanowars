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

#include "Util/Matrix.hpp"
#include "Math/Vector2.hpp"
#include "Asset/AssetHolder.hpp"

#include <SFML/Graphics/Image.hpp>

namespace nanowars {
namespace algorithms {

    using util::Matrix;
    using math::Vector2u;
    using asset::AssetHolder;
    using sf::Image;

    class CaveGenerator
    {
    public:
        CaveGenerator();

        Matrix<bool> getRandomCave(Vector2u size);
        Image getRandomTexturedCave(Vector2u size, AssetHolder& assetHolder);

    private:
        Matrix<bool> scale(Matrix<bool>& matrix, Vector2u scale);
        void initMatrices(Matrix<bool>& matrix1, Matrix<bool>& matrix2, float wallProbability);
        void performGeneration(Matrix<bool>& matrix, Matrix<bool>& matrix2, int r1CutOff, int r2CutOff);
    };
}
}