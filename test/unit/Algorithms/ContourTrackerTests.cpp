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

#include "Algorithms/ContourTracer.hpp"
#include "Util/ImageAccessorSfmlImpl.hpp"

#include <SFML/Graphics/Image.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/progress.hpp>
#include <catch2/catch.hpp>

namespace fs = boost::filesystem;
using namespace std;
using namespace nanowars::algorithms;
using namespace nanowars::util;

TEST_CASE("ContourTracer correctly generates contours in all test datasets")
{
    fs::path dataPath(fs::initial_path<fs::path>().branch_path() / "test" / "data" / "Algorithms" / "ContourTracer");

    fs::directory_iterator endIter;
    for (fs::directory_iterator dirIter(dataPath); dirIter != endIter; ++dirIter)
    {
        auto& sourcePath = dirIter->path();
        if (sourcePath.string().find(".assertion.") != string::npos)
            continue;

        sf::Image sourceImage;
        REQUIRE(sourceImage.loadFromFile(sourcePath.string()));

        const auto& contours = ContourTracer::findContours(ImageAccessorSfmlImpl(sourceImage));

        for (auto& contour : contours)
        {
            for (int i = 0; i < contour.size(); ++i)
            {
                sourceImage.setPixel(contour[i].x, contour[i].y, sf::Color::Red);
            }
        }

        auto assertionPath = dataPath / (sourcePath.stem().string() + ".assertion" + sourcePath.extension().string());
#ifdef GENERATE_ASSERTIONS
        sourceImage.saveToFile(assertionPath.string());
#else
        sf::Image assertionImage;
        REQUIRE(assertionImage.loadFromFile(assertionPath.string()));

        auto* sourcePtr = sourceImage.getPixelsPtr();
        auto* assertionPtr = assertionImage.getPixelsPtr();
        for (long i = 0; i < sourceImage.getSize().x * sourceImage.getSize().y * 4; ++i)
        {
            REQUIRE(*sourcePtr == *assertionPtr);
            sourcePtr++;
            assertionPtr++;
        }
#endif
    }
}