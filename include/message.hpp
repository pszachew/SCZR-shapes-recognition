#pragma once

#include <cstdint>
#include <chrono>
#include <opencv2/opencv.hpp>
//typedef std::chrono::time_point<std::chrono::system_clock> time_point;

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

typedef struct ProcBC
{
    cv::Mat threshold;
    cv::Mat cameraFeed;
} ProcBC;

typedef struct ProcCD
{
  std::chrono::high_resolution_clock::time_point time_point;
} ProcCD;

typedef struct ProcBD
{
  std::chrono::high_resolution_clock::time_point time_point;
} ProcBD;