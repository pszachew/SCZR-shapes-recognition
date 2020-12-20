//program to set proper HSV filters

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

int H_MIN = 0;
int H_MAX = 256;
int S_MIN = 0;
int S_MAX = 256;
int V_MIN = 0;
int V_MAX = 256;

void on_trackbar( int, void* )
{//This function gets called whenever a
	// trackbar position is changed
}

void createTrackbars(){
	//create window for trackbars
    cv::namedWindow("Trackbar",0);
	//create memory to store trackbar name on window
	char TrackbarName[50];
	sprintf( TrackbarName, "H_MIN", H_MIN);
	sprintf( TrackbarName, "H_MAX", H_MAX);
	sprintf( TrackbarName, "S_MIN", S_MIN);
	sprintf( TrackbarName, "S_MAX", S_MAX);
	sprintf( TrackbarName, "V_MIN", V_MIN);
	sprintf( TrackbarName, "V_MAX", V_MAX);
	//create trackbars and insert them into window
	//3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
	//the max value the trackbar can move (eg. H_HIGH), 
	//and the function that is called whenever the trackbar is moved(eg. on_trackbar)
	//                                  ---->    ---->     ---->      
    cv::createTrackbar( "H_MIN", "Trackbar", &H_MIN, H_MAX, on_trackbar );
    cv::createTrackbar( "H_MAX", "Trackbar", &H_MAX, H_MAX, on_trackbar );
    cv::createTrackbar( "S_MIN", "Trackbar", &S_MIN, S_MAX, on_trackbar );
    cv::createTrackbar( "S_MAX", "Trackbar", &S_MAX, S_MAX, on_trackbar );
    cv::createTrackbar( "V_MIN", "Trackbar", &V_MIN, V_MAX, on_trackbar );
    cv::createTrackbar( "V_MAX", "Trackbar", &V_MAX, V_MAX, on_trackbar );
}

void saveConfig(){
    std::ofstream config_file;
    config_file.open("config.txt");
    config_file << H_MIN << std::endl;
    config_file << S_MIN << std::endl;
    config_file << V_MIN << std::endl;
    config_file << H_MAX << std::endl;
    config_file << S_MAX << std::endl;
    config_file << V_MAX << std::endl;
    config_file.close();
}

int main(){

    cv::VideoCapture capture(0);
	cv::Mat cameraFeed, HSV, threshold;

    if(!capture.isOpened()){
        return -1;
    }

    createTrackbars();

    while(cv::waitKey(30) != ' '){
        capture.read(cameraFeed);

        cv::cvtColor(cameraFeed,HSV,cv::COLOR_BGR2HSV);
        cv::inRange(HSV,cv::Scalar(H_MIN,S_MIN,V_MIN),cv::Scalar(H_MAX,S_MAX,V_MAX),threshold);

        cv::imshow("Original",cameraFeed);
        cv::imshow("Filtered",threshold);
    }

    saveConfig();
}
