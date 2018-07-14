#include <vector>
#include <random>
#include <algorithm>

#pragma once

class Solver
{
public:
    Solver() = default;
    ~Solver() = default;
    std::vector<cv::Point> solve(const std::vector<cv::Point>& old_cities, std::mt19937& rng)
    {
        auto new_cities = old_cities;
        std::shuffle(new_cities.begin(), new_cities.end(), rng);
        return new_cities;
    }
};
