//proccess responsible for finding an object

#include <iostream>
#include <opencv2/opencv.hpp>


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

    std::cout << H_MIN << std::endl;
    std::cout << S_MIN << std::endl;
    std::cout << V_MIN << std::endl;
    std::cout << H_MAX << std::endl;
    std::cout << S_MAX << std::endl;
    std::cout << V_MAX << std::endl;
}

int main(){

    cv::VideoCapture capture(0);
	cv::Mat cameraFeed, HSV, threshold;

    if(!capture.isOpened()){
        return -1;
    }
    loadConfig();
    while(1){
        capture.read(cameraFeed);

        cv::cvtColor(cameraFeed,HSV,cv::COLOR_BGR2HSV);
        cv::inRange(HSV,cv::Scalar(H_MIN,S_MIN,V_MIN),cv::Scalar(H_MAX,S_MAX,V_MAX),threshold);

        cv::imshow("Original",cameraFeed);
        cv::imshow("HSV",HSV);
        cv::imshow("Filtered",threshold);
        cv::waitKey(30);
    }

}