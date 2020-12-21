//proccess responsible for finding an object

#include <iostream>
#include "opencv2/opencv.hpp"
#include "pqueue.hpp"



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

    std::cout<<"convert"<<std::endl;

	cv::Mat HSV, threshold;

    loadConfig();

    ProcAB m_in;
    ProcBC m_outC;
    ProcBD m_outD;
    int shmidA = shmget(KEY_A, sizeof(PQueue<ProcAB>), 0);
    PQueue<ProcAB> *pqA = (PQueue<ProcAB> *)shmat(shmidA, NULL, 0);
    
    int shmidB = shmget(KEY_B, sizeof(PQueue<ProcBC>),0);
    PQueue<ProcBC> *pqB = (PQueue<ProcBC> *)shmat(shmidB, NULL, 0);

    int shmidD = shmget(KEY_D, sizeof(PQueue<ProcBD>),0);
    PQueue<ProcBD> *pqD = (PQueue<ProcBD> *)shmat(shmidD, NULL, 0);
   
    m_in.A_delayOut = 0;
   m_outC.B_delayOut = 0;
    while(cv::waitKey(30) != ' '){

        auto t1 = std::chrono::high_resolution_clock::now();
        down(pqA->getSemid(), FULL);
        down(pqA->getSemid(), BIN);
        
        m_in=pqA->pop();
        
        up(pqA->getSemid(), BIN);
        up(pqA->getSemid(), EMPTY);
        auto t2 = std::chrono::high_resolution_clock::now();
        m_outC.B_delayIn = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();

        cv::Mat cameraFeed(FRAME_WIDTH, FRAME_HEIGHT, CV_8UC3, m_in.img);
        cv::cvtColor(cameraFeed,HSV,cv::COLOR_BGR2HSV); //convert to HSV
        cv::inRange(HSV,cv::Scalar(H_MIN,S_MIN,V_MIN),cv::Scalar(H_MAX,S_MAX,V_MAX),threshold); //threshold image based of config filters
        cv::blur(threshold, threshold, cv::Size(5, 5), cv::Point(-1, -1));
        cv::Mat erodeElement = cv::getStructuringElement( cv::MORPH_RECT,cv::Size(3,3));
        cv::erode(threshold,threshold,erodeElement);
        cv::erode(threshold,threshold,erodeElement);
        cv::Mat dilateElement = cv::getStructuringElement( cv::MORPH_RECT,cv::Size(5,5));
        cv::dilate(threshold,threshold,dilateElement);
        cv::dilate(threshold,threshold,dilateElement);

        memcpy(&m_outC.cameraFeed, cameraFeed.data, sizeof(uint8_t) * IMG_SIZE);
        memcpy(&m_outC.threshold, threshold.data, sizeof(uint8_t) * IMG_SIZE/3);

        m_outC.A_delayOut = m_in.A_delayOut;

        t1 = std::chrono::high_resolution_clock::now();
        down(pqB->getSemid(), EMPTY);
        down(pqB->getSemid(), BIN);        
        
        pqB->push(&m_outC);
        
        up(pqB->getSemid(), BIN);
        up(pqB->getSemid(), FULL);
        t2 = std::chrono::high_resolution_clock::now();
        m_outC.B_delayOut = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();

        // m_outD.receive_ts = receive_ts;
        // m_outD.send_ts = m_in.send_ts;

        // down(pqD->getSemid(), EMPTY);
        // down(pqD->getSemid(), BIN);        
        
        // pqD->push(&m_outD);
        
        // up(pqD->getSemid(), BIN);
        // up(pqD->getSemid(), FULL);

    }

}