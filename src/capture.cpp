//Proccess that captures video frames from camera
//and send them to the next proccess

#include <opencv2/opencv.hpp>

int main(){

    cv::VideoCapture capture(0);
	cv::Mat cameraFeed;

    if(!capture.isOpened()){
        return -1;
    }

    while(capture.read(cameraFeed && cv::waitKey(30) != ' ')){
        cv::imshow("Original",cameraFeed);

        
    }
}