#pragma once

#include <vector>
#include <random>

class Solver
{
public:
    virtual ~Solver() = default;
    virtual void solve(std::vector<cv::Point>& cities, std::mt19937& rng) = 0;
};
