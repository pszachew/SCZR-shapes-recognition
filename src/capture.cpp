//Proccess that captures video frames from camera
//and send them to the next proccess

#include <sstream>
#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int H_MIN = 0;
int H_MAX = 256;
int S_MIN = 0;
int S_MAX = 256;
int V_MIN = 0;
int V_MAX = 256;


int main(int argc, char* argv[]){

    VideoCapture capture(0);
	Mat cameraFeed;

    if(!capture.isOpened()){
        return -1;
    }
	capture.set(CAP_PROP_FRAME_WIDTH,FRAME_WIDTH);

    while(1){
        capture.read(cameraFeed);
        imshow("Original",cameraFeed);
        waitKey(30);
    }

}