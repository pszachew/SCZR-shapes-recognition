#pragma once

#include <cstdint>
#include <chrono>
#include <opencv2/opencv.hpp>

#define FRAME_HEIGHT 640
#define FRAME_WIDTH 480
#define IMG_SIZE FRAME_HEIGHT * FRAME_WIDTH * 3


typedef struct ProcAB
{
    uint8_t img[IMG_SIZE];
    std::chrono::high_resolution_clock::time_point send_ts;
} ProcAB;

typedef struct ProcBC
{
    uint8_t threshold[IMG_SIZE];
    uint8_t cameraFeed[IMG_SIZE];
    std::chrono::high_resolution_clock::time_point send_ts;
} ProcBC;

typedef struct ProcCD
{
  std::chrono::high_resolution_clock::time_point receive_ts;
  std::chrono::high_resolution_clock::time_point send_ts;
  std::chrono::high_resolution_clock::time_point show_ts;
} ProcCD;

typedef struct ProcBD
{
  std::chrono::high_resolution_clock::time_point receive_ts;
  std::chrono::high_resolution_clock::time_point send_ts;
} ProcBD;