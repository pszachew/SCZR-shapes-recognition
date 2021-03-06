//Proccess that captures video frames from camera
//and send them to the next proccess

#include <opencv2/opencv.hpp>
#include "pqueue.hpp"


int main(){

    std::cout<<"Camera capture running"<<std::endl;

    cv::VideoCapture capture(0);
	cv::Mat cameraFeed;

    int shmidA = shmget(KEY_A, sizeof(PQueue<ProcAB>), 0); //creating shared memory between process A(capturing) and B(convert)
    PQueue<ProcAB> *pqA = (PQueue<ProcAB> *)shmat(shmidA, NULL, 0);
    ProcAB message;
    if(!capture.isOpened()){
        return -1;
    }

    while(capture.read(cameraFeed))
    {
        cv::waitKey(DELAY);
        cv::imshow("Camera",cameraFeed);
        cv::Mat resized;
        cv::resize(cameraFeed, resized,cv::Size(FRAME_HEIGHT, FRAME_WIDTH));

        memcpy(&message.img, resized.data, sizeof(uint8_t) * IMG_SIZE);
        
        message.timestamp = std::chrono::high_resolution_clock::now();
        down(pqA->getSemid(), EMPTY);
        down(pqA->getSemid(), BIN);

        pqA->push(&message);

        up(pqA->getSemid(), BIN);
        up(pqA->getSemid(), FULL);

    }
}