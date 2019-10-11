#include "Algorithms/LaunchPadFinder.hpp"

namespace nanowars {
namespace algorithms {

    vector<Vector2f> LaunchPadFinder::getBestLaunchPodPositions(b2Body& landscape)
    {
        vector<Vector2f> positions;
        positions.emplace_back(50.0f, 0.0f);
        return positions;
    }
}
}