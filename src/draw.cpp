//proccess responsible for finding an object

#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"

int main(){
	cv::Mat cameraFeed, threshold;
    
    while(cv::waitKey(30) != ' '){
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