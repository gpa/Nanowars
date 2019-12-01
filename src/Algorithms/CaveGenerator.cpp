#include "Algorithms/CaveGenerator.hpp"
#include "Algorithms/Randomizer.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

namespace nanowars {
namespace algorithms {

    using sf::Color;

    CaveGenerator::CaveGenerator()
    {
    }

    Matrix<bool> CaveGenerator::getRandomCave(Vector2u size)
    {
        Vector2u generationSize = { 70, 20 };
        Matrix<bool> matrix1(generationSize);
        Matrix<bool> matrix2(generationSize);

        initMatrices(matrix1, matrix2, 40.0f);

        for (int i = 0; i < 4; ++i)
            performGeneration(matrix1, matrix2, 5, 2);

        for (int i = 0; i < 3; ++i)
            performGeneration(matrix1, matrix2, 5, 0);

        return scale(matrix1, size);
    }

    void CaveGenerator::initMatrices(Matrix<bool>& matrix1, Matrix<bool>& matrix2, float wallProbability)
    {
        auto generationSize = matrix1.getSize();
        for (unsigned y = 0; y < generationSize.y; ++y)
        {
            for (unsigned x = 0; x < generationSize.x; ++x)
            {
                if (x == 0 || x == generationSize.x - 1 || y == 0 || y == generationSize.y - 1)
                    matrix1.setAt(x, y, true);
                else if (Randomizer::getRandom(0, 100) < wallProbability)
                    matrix1.setAt(x, y, true);

                matrix2.setAt(x, y, true);
            }
        }
    }

    void CaveGenerator::performGeneration(Matrix<bool>& matrix1, Matrix<bool>& matrix2, int r1CutOff, int r2CutOff)
    {
        // Original code by http://www.roguebasin.com/index.php?title=Jim_Babcock&action=edit&redlink=1
        unsigned size_y = matrix1.getSize().y;
        unsigned size_x = matrix1.getSize().x;

        for (unsigned y = 1; y < size_y - 1; y++)
        {
            for (unsigned x = 1; x < size_x - 1; x++)
            {
                int adjcount_r1 = 0,
                    adjcount_r2 = 0;

                for (int ii = -1; ii <= 1; ii++)
                {
                    for (int jj = -1; jj <= 1; jj++)
                    {
                        if (matrix1.getAt(x + jj, y + ii))
                            adjcount_r1++;
                    }
                }

                for (int ii = y - 2; ii <= y + 2; ii++)
                {
                    for (int jj = x - 2; jj <= x + 2; jj++)
                    {
                        if (abs((int)(ii - y)) == 2 && abs((int)(jj - x)) == 2)
                            continue;

                        if (ii < 0 || jj < 0 || static_cast<unsigned>(ii) >= size_y || static_cast<unsigned>(jj) >= size_x)
                            continue;

                        if (matrix1.getAt(static_cast<unsigned>(jj), static_cast<unsigned>(ii)))
                            adjcount_r2++;
                    }
                }

                matrix2.setAt(x, y, adjcount_r1 >= r1CutOff || adjcount_r2 <= r2CutOff);
            }
        }

        for (unsigned y = 1; y < size_y - 1; y++)
        {
            for (unsigned x = 1; x < size_x - 1; x++)
                matrix1.setAt(x, y, matrix2.getAt(x, y));
        }
    }

    Image CaveGenerator::getRandomTexturedCave(Vector2u size, AssetHolder& assetHolder)
    {
        Matrix<bool> cave = getRandomCave(size);
        Image image;
        image.create(size.x, size.y);

        for (unsigned y = 0; y < size.y; ++y)
            for (unsigned x = 0; x < size.x; ++x)
                image.setPixel(x, y, cave.getAt(x, y) ? Color::Black : Color::Transparent);

        return image;
    }

    Matrix<bool> CaveGenerator::scale(Matrix<bool>& matrix, Vector2u size)
    {
        Matrix<bool> scaledMatrix(size);

        auto originalSize = matrix.getSize();

        for (unsigned int y = 0; y < size.y; ++y)
        {
            for (unsigned int x = 0; x < size.x; ++x)
            {
                unsigned int ox = static_cast<unsigned int>(static_cast<double>(x) / size.x * originalSize.x);
                unsigned int oy = static_cast<unsigned int>(static_cast<double>(y) / size.y * originalSize.y);
                scaledMatrix.setAt(x, y, matrix.getAt(ox, oy));
            }
        }
        return scaledMatrix;
    }
}
}