#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <set>
#include <random>
#include <algorithm>
#include <limits>
 
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

    std::uniform_int_distribution<std::mt19937::result_type> initialize_random_number_generator()
    {
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> rand(point_size,
                                                                      window_size - point_size);
        return rand;
    }
 
    void generate_cities(size_t cities_quantity, std::uniform_int_distribution<std::mt19937::result_type> rand)
    {
        auto cmp = [](const cv::Point& lhs, const cv::Point& rhs) { return lhs.x>rhs.x or (lhs.x==rhs.x and lhs.y>rhs.y); };
        std::set<cv::Point, decltype(cmp)> non_unique_cities(cmp);

        for(size_t i=0; i<cities_quantity; ++i)
            non_unique_cities.emplace(rand(rng), rand(rng));

        cities.reserve(cities_quantity);
        cities.assign(non_unique_cities.begin(), non_unique_cities.end());
        cities.shrink_to_fit();
    }

    void create_window()
    {
        image = cv::Mat::zeros(window_size, window_size, CV_8UC3);
    }

    void draw_cities()
    {
        for(auto point : cities)
            cv::circle(image, point, point_size, cv::Scalar(255, 255, 255), cv::FILLED, 8);
    }

    void count_distance_and_draw_lines()
    {
        actual_distance = 0.0;
        for(size_t i=0; i<cities.size()-1; ++i)
        {
            actual_distance += std::sqrt(pow(cities[i].x - cities[i+1].x, 2) +
                                         pow(cities[i].y - cities[i+1].y, 2));
            cv::line(image, cities[i], cities[i+1], cv::Scalar(0, 255, 0));
        }
        if(actual_distance < minimal_distance)
        {
            std::cout << actual_distance << std::endl;
            minimal_distance = actual_distance;
            cv::imshow("tsp", image);
            cv::waitKey(10);
        }
    }

public:
    Simulation(size_t cities_quantity = 50)
    {
        auto rand = initialize_random_number_generator();
        generate_cities(cities_quantity, rand);
    }

    void run()
    {
        while(true)
        {
            create_window();
            std::shuffle(cities.begin(), cities.end(), rng);
            draw_cities();
            count_distance_and_draw_lines();
        }
    }
};