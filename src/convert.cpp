//proccess responsible for finding an object

#include <iostream>
#include "opencv2/opencv.hpp"

int H_MIN = 0;
int S_MIN = 0;
int V_MIN = 0;
int H_MAX = 256;
int S_MAX = 256;
int V_MAX = 256;

void loadConfig(){
    std::ifstream config_file;
    config_file.open("config.txt");
    config_file >> H_MIN;
    config_file >> S_MIN;
    config_file >> V_MIN;
    config_file >> H_MAX;
    config_file >> S_MAX;
    config_file >> V_MAX;
}

int main(){
	cv::Mat cameraFeed, HSV, threshold;

    loadConfig();

    while(cv::waitKey(30) != ' '){

        cv::cvtColor(cameraFeed,HSV,cv::COLOR_BGR2HSV); //convert to HSV
        cv::inRange(HSV,cv::Scalar(H_MIN,S_MIN,V_MIN),cv::Scalar(H_MAX,S_MAX,V_MAX),threshold); //threshold image based of config filters

        
    }

}