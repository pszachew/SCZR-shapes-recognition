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
	cv::Mat cameraFeed, HSV, threshold;

    loadConfig();

    ProcAB m_in;
    ProcBC m_out;
    int shmidA = shmget(KEY_A, sizeof(PQueue<ProcAB>), 0);
    PQueue<ProcAB> *pqA = (PQueue<ProcAB> *)shmat(shmidA, NULL, 0);
    
    int shmidB = shmget(KEY_B, sizeof(PQueue<ProcBC>),0);
    PQueue<ProcBC> *pqB = (PQueue<ProcBC> *)shmat(shmidB, NULL, 0);
   
    while(cv::waitKey(30) != ' '){

        auto t1 = std::chrono::high_resolution_clock::now(); //receive image - timestamp

        down(pqA->getSemid(), FULL);
        down(pqA->getSemid(), BIN);        
        
        m_in=pqA->pop();
        
        up(pqA->getSemid(), BIN);
        up(pqA->getSemid(), EMPTY);

        cameraFeed=m_in.img;
        cv::cvtColor(cameraFeed,HSV,cv::COLOR_BGR2HSV); //convert to HSV
        cv::inRange(HSV,cv::Scalar(H_MIN,S_MIN,V_MIN),cv::Scalar(H_MAX,S_MAX,V_MAX),threshold); //threshold image based of config filters

        m_out.cameraFeed=cameraFeed;
        m_out.threshold=threshold;
        
        down(pqB->getSemid(), FULL);
        down(pqB->getSemid(), BIN);        
        
        pqB->push(&m_out);
        
        up(pqB->getSemid(), BIN);
        up(pqB->getSemid(), EMPTY);

        auto t2 = std::chrono::high_resolution_clock::now(); // show images - timestamp
    }

}