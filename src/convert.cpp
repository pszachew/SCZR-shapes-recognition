//proccess responsible for finding an object

#include <iostream>
#include <vector>
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
    cv::VideoCapture capture(0);
	cv::Mat cameraFeed, HSV, threshold;

    capture.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    if(!capture.isOpened()){
        return -1;
    }
    loadConfig();

    while(capture.read(cameraFeed) && cv::waitKey(30) != ' '){

        cv::cvtColor(cameraFeed,HSV,cv::COLOR_BGR2HSV);
        cv::inRange(HSV,cv::Scalar(H_MIN,S_MIN,V_MIN),cv::Scalar(H_MAX,S_MAX,V_MAX),threshold);

        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;
        findContours( threshold, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE );

        cv::Mat drawing = cv::Mat::zeros(cameraFeed.size(), CV_8UC3);
        for( size_t i = 0; i < contours.size(); i++ ){
            drawContours(cameraFeed, contours, (int)i, cv::Scalar(255, 0, 0), 2, cv::LINE_8, hierarchy, 0);
        }

        cv::imshow("Original",cameraFeed);
        cv::imshow("Filtered",threshold);
    }

}