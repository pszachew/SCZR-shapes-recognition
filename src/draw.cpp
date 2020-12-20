//proccess responsible for finding an object

#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"
#include "pqueue.hpp"

int main(){

    std::cout<<"draw"<<std::endl;

	cv::Mat cameraFeed, threshold;
    ProcBC m_in;
    ProcCD m_out;

    
    int shmidC = shmget(KEY_C, sizeof(PQueue<ProcCD>), 0);
    PQueue<ProcCD> *pqC = (PQueue<ProcCD> *)shmat(shmidC, NULL, 0);

    int shmidB = shmget(KEY_B, sizeof(PQueue<ProcBC>),0);
    PQueue<ProcBC> *pqB = (PQueue<ProcBC> *)shmat(shmidB, NULL, 0);

    while(cv::waitKey(30) != ' '){

        auto t1 = std::chrono::high_resolution_clock::now(); //receive images - timestamp

        down(pqB->getSemid(), FULL);
        down(pqB->getSemid(), BIN);        
        
        m_in=pqB->pop();
        
        up(pqB->getSemid(), BIN);
        up(pqB->getSemid(), EMPTY);
        cameraFeed=m_in.cameraFeed;
        threshold=m_in.threshold;
        
        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;
        findContours( threshold, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE );

        cv::Mat drawing = cv::Mat::zeros(cameraFeed.size(), CV_8UC3);
        for( size_t i = 0; i < contours.size(); i++ ){
            drawContours(cameraFeed, contours, (int)i, cv::Scalar(255, 0, 0), 2, cv::LINE_8, hierarchy, 0);
        }

        auto t2 = std::chrono::high_resolution_clock::now(); // show images - timestamp

        m_out.time_in=t1;
        m_out.time_out=t2;

        down(pqC->getSemid(), EMPTY);
        down(pqC->getSemid(), BIN);        
        
        pqC->push(&m_out);
        
        up(pqC->getSemid(), BIN);
        up(pqC->getSemid(), FULL);

        cv::imshow("Original",cameraFeed);
        cv::imshow("Filtered",threshold);
        
    }

}