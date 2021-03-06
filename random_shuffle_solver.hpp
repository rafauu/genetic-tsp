#pragma once

#include <algorithm>
#include "solver.hpp"

class RandomShuffleSolver : public Solver
{
public:
    void solve(std::vector<cv::Point>& cities, std::mt19937& rng) override
    {
        std::shuffle(cities.begin(), cities.end(), rng);
    }
};
