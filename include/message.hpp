#pragma once

#include <cstdint>
#include <chrono>
#include <opencv2/opencv.hpp>
typedef std::chrono::time_point<std::chrono::system_clock> time_point;

typedef struct Timestamp 
{
    time_point init_time;
    time_point push_time;
    time_point pop_time;
} Timestamp;

typedef struct ProcAB
{
    cv::Mat img;
} ProcAB;