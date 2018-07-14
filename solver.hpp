#include <vector>
#include <random>

#pragma once

class Solver
{
public:
    virtual ~Solver() = default;
    virtual void solve(std::vector<cv::Point>& cities, std::mt19937& rng) = 0;
};
