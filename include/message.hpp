#pragma once

#include <cstdint>
#include <opencv2/opencv.hpp>

#define DELAY 10
#define FRAME_HEIGHT 640
#define FRAME_WIDTH 480
#define IMG_SIZE FRAME_HEIGHT * FRAME_WIDTH * 3


typedef struct ProcAB
{
    uint8_t img[IMG_SIZE];
    std::chrono::high_resolution_clock::time_point timestamp;
} ProcAB;

typedef struct ProcBC
{
    uint8_t threshold[IMG_SIZE];
    uint8_t cameraFeed[IMG_SIZE];
    std::chrono::high_resolution_clock::time_point timestamp;
} ProcBC;

typedef struct ProcCD
{
    int BC_delay;
    std::chrono::high_resolution_clock::time_point timestamp;
} ProcCD;

typedef struct ProcBD
{
    int AB_delay;
    std::chrono::high_resolution_clock::time_point timestamp;
} ProcBD;
