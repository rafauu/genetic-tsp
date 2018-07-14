#include <opencv2/core/core.hpp>
#include <limits>
#include <vector>
#include <random>
#include "solver.hpp"

#pragma once

class Simulation
{
private:
    static constexpr size_t window_size = 500;
    static constexpr size_t point_size = 3;
    cv::Mat image;
    double minimal_distance = std::numeric_limits<double>::max();
    double actual_distance = 0.0;
    std::vector<cv::Point> cities;
    std::mt19937 rng;
    Solver solver;

    std::uniform_int_distribution<std::mt19937::result_type> initialize_random_number_generator();
    void generate_cities(size_t cities_quantity, std::uniform_int_distribution<std::mt19937::result_type> rand);
    void create_window();
    void draw_cities();
    void count_distance_and_draw_lines();

public:
    Simulation(size_t cities_quantity = 50);
    void run();
};
