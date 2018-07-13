#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <random>
#include <algorithm>
 
int main()
{    
    cv::Mat image = cv::Mat::zeros(400, 400, CV_8UC3);
    std::vector<cv::Point> points;

    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> rand(1, 400);

    for(size_t i=0; i<100; ++i)
        points.emplace_back(cv::Point(rand(rng), rand(rng)));

    points.erase(std::unique(points.begin(), points.end()), points.end());

    double distance = 0.0;
    for(size_t i=0; i<points.size()-1; ++i)
    {
        distance += std::sqrt(pow(points[i].x - points[i+1].x, 2) +
                              pow(points[i].y - points[i+1].y, 2));
        cv::line(image, points[i], points[i+1], cv::Scalar(0, 255, 0));
    }
    std::cout << distance;

    for(auto point : points)
        cv::circle(image, point, 3.0, cv::Scalar(255, 255, 255), cv::FILLED, 8);

    cv::imshow("tsp", image);
 
    cv::waitKey(0);
    return(0);
}
