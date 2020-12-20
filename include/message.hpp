#pragma once

#include <cstdint>
#include <chrono>
#include <opencv2/opencv.hpp>


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
  std::chrono::high_resolution_clock::time_point time_in;
  std::chrono::high_resolution_clock::time_point time_out;
} ProcCD;

typedef struct ProcBD
{
  std::chrono::high_resolution_clock::time_point time_in;
  std::chrono::high_resolution_clock::time_point time_out;
} ProcBD;