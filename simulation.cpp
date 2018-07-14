#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <set>
#include <algorithm>
#include "simulation.hpp"
 
std::uniform_int_distribution<std::mt19937::result_type> Simulation::initialize_random_number_generator()
{
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> rand(point_size,
                                                                  window_size - point_size);
    return rand;
}

void Simulation::generate_cities(size_t cities_quantity, std::uniform_int_distribution<std::mt19937::result_type> rand)
{
    auto cmp = [](const cv::Point& lhs, const cv::Point& rhs) { return lhs.x>rhs.x or (lhs.x==rhs.x and lhs.y>rhs.y); };
    std::set<cv::Point, decltype(cmp)> non_unique_cities(cmp);

    for(size_t i=0; i<cities_quantity; ++i)
        non_unique_cities.emplace(rand(rng), rand(rng));

    cities.reserve(cities_quantity);
    cities.assign(non_unique_cities.begin(), non_unique_cities.end());
    cities.shrink_to_fit();
    std::shuffle(cities.begin(), cities.end(), rng);
}

void Simulation::create_window()
{
    image = cv::Mat::zeros(window_size, window_size, CV_8UC3);
}

void Simulation::draw_cities()
{
    for(auto point : cities)
        cv::circle(image, point, point_size, cv::Scalar(255, 255, 255), cv::FILLED, 8);
}

void Simulation::count_distance_and_draw_lines()
{
    actual_distance = 0.0;
    for(size_t i=0; i<cities.size(); ++i)
    {
        actual_distance += std::sqrt(pow(cities[i].x - cities[(i+1)%cities.size()].x, 2) +//consider removing sqrt
                                     pow(cities[i].y - cities[(i+1)%cities.size()].y, 2));
        cv::line(image, cities[i], cities[(i+1)%cities.size()], cv::Scalar(0, 255, 0));
    }
    if(actual_distance < minimal_distance)
    {
        std::cout << actual_distance << std::endl;
        minimal_distance = actual_distance;
        cv::imshow("tsp", image);
        cv::waitKey(50);
    }
    cv::waitKey(1);
}

Simulation::Simulation(size_t cities_quantity)
{
    auto rand = initialize_random_number_generator();
    generate_cities(cities_quantity, rand);
}

void Simulation::run()
{
    while(true)
    {
        create_window();
        solver->solve(cities, rng);
        draw_cities();
        count_distance_and_draw_lines();
    }
}
