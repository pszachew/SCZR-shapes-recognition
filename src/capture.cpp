//Proccess that captures video frames from camera
//and send them to the next proccess

#include <opencv2/opencv.hpp>
#include "pqueue.hpp"


int main(){

    std::cout<<"capture"<<std::endl;

    cv::VideoCapture capture(0);
	cv::Mat cameraFeed;

    int shmidA = shmget(KEY_A, sizeof(PQueue<ProcAB>), 0); //creating shared memory between process A(capturing) and B(convert)
    PQueue<ProcAB> *pqA = (PQueue<ProcAB> *)shmat(shmidA, NULL, 0);
    ProcAB message;
    if(!capture.isOpened()){
        return -1;
    }

    message.A_delayOut = 0;
    while(capture.read(cameraFeed) && cv::waitKey(30) != ' ')
    {
        cv::imshow("Camera",cameraFeed);
        cv::Mat resized;
        cv::resize(cameraFeed, resized,cv::Size(FRAME_HEIGHT, FRAME_WIDTH));

        memcpy(&message.img, resized.data, sizeof(uint8_t) * IMG_SIZE);
        
        auto t1 = std::chrono::high_resolution_clock::now();
        down(pqA->getSemid(), EMPTY);
        down(pqA->getSemid(), BIN);

        pqA->push(&message);

        up(pqA->getSemid(), BIN);
        up(pqA->getSemid(), FULL);
        auto t2 = std::chrono::high_resolution_clock::now();

        message.A_delayOut = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();

    }
}