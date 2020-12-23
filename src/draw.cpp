//proccess responsible for finding an object

#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"
#include "pqueue.hpp"

int main(){

    std::cout<<"Shape tracking running"<<std::endl;

    ProcBC m_in;
    ProcCD m_out;
    
    int shmidC = shmget(KEY_C, sizeof(PQueue<ProcCD>), 0);
    PQueue<ProcCD> *pqC = (PQueue<ProcCD> *)shmat(shmidC, NULL, 0);

    int shmidB = shmget(KEY_B, sizeof(PQueue<ProcBC>),0);
    PQueue<ProcBC> *pqB = (PQueue<ProcBC> *)shmat(shmidB, NULL, 0);

    while(1){
        cv::waitKey(DELAY);
        down(pqB->getSemid(), FULL);
        down(pqB->getSemid(), BIN);        
        
        m_in=pqB->pop();
        
        up(pqB->getSemid(), BIN);
        up(pqB->getSemid(), EMPTY);
        auto t = std::chrono::high_resolution_clock::now();
        m_out.BC_delay = std::chrono::duration_cast<std::chrono::milliseconds>( t - m_in.timestamp ).count();

        cv::Mat cameraFeed(FRAME_WIDTH, FRAME_HEIGHT, CV_8UC3, m_in.cameraFeed);
        cv::Mat threshold(FRAME_WIDTH, FRAME_HEIGHT, CV_8UC1, m_in.threshold);
        
        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;
        findContours( threshold, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE );

        cv::Mat drawing = cv::Mat::zeros(cameraFeed.size(), CV_8UC3);
        for( size_t i = 0; i < contours.size(); i++ ){
            cv::approxPolyDP(contours[i], contours[i], 0.01 * cv::arcLength(contours[i], true), true);
            drawContours(cameraFeed, contours, (int)i, cv::Scalar(255, 0, 0), 2, cv::LINE_4, hierarchy, 0);
        }

        cv::imshow("Draw",cameraFeed);

        m_out.timestamp = std::chrono::high_resolution_clock::now();
        down(pqC->getSemid(), EMPTY);
        down(pqC->getSemid(), BIN);        
        
        pqC->push(&m_out);
        
        up(pqC->getSemid(), BIN);
        up(pqC->getSemid(), FULL);
    }
}