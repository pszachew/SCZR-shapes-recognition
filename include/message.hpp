#pragma once

#include <cstdint>
#include <chrono>
#include <opencv2/opencv.hpp>

#define MAX_PIXELS 640
#define IMG_SIZE MAX_PIXELS * MAX_PIXELS * 3


typedef struct ProcAB
{
    uint8_t img[IMG_SIZE];
} ProcAB;

typedef struct ProcBC
{
    uint8_t threshold[IMG_SIZE];
    uint8_t cameraFeed[IMG_SIZE];
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