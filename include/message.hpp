#pragma once

#include <cstdint>
#include <opencv2/opencv.hpp>

#define FRAME_HEIGHT 640
#define FRAME_WIDTH 480
#define IMG_SIZE FRAME_HEIGHT * FRAME_WIDTH * 3


typedef struct ProcAB
{
    uint8_t img[IMG_SIZE];
    int A_delayOut;
} ProcAB;

typedef struct ProcBC
{
    uint8_t threshold[IMG_SIZE];
    uint8_t cameraFeed[IMG_SIZE];
    int A_delayOut;
    int B_delayIn;
    int B_delayOut;
} ProcBC;

typedef struct ProcCD
{
    int A_delayOut;
    int B_delayIn;
    int B_delayOut;
    int C_delayIn;
    int C_delayOut;
} ProcCD;

typedef struct ProcBD
{
    int receive_ts;
    int send_ts;
} ProcBD;