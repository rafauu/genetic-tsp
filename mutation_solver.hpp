#pragma once

#include <algorithm>
#include "solver.hpp"

class MutationSolver : public Solver
{
public:
    void solve(std::vector<cv::Point>& cities, std::mt19937& rng) override
    {
        std::uniform_int_distribution<std::mt19937::result_type> rand(0, cities.size()-1);
        for(auto i=0; i<3; ++i)
            std::iter_swap(cities.begin() + rand(rng), cities.begin() + rand(rng));
    }
};
