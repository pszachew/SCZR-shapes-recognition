//Proccess that captures video frames from camera
//and send them to the next proccess

#include <opencv2/opencv.hpp>
#include "pqueue.hpp"


int main(){

    std::cout<<"capture"<<std::endl;

    cv::VideoCapture capture(0);

    capture.set(cv::CAP_PROP_FRAME_WIDTH,FRAME_HEIGHT);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT,FRAME_WIDTH);
	cv::Mat cameraFeed;

    int shmidA = shmget(KEY_A, sizeof(PQueue<ProcAB>), 0); //creating shared memory between process A(capturing) and B(convert)
    PQueue<ProcAB> *pqA = (PQueue<ProcAB> *)shmat(shmidA, NULL, 0);
    ProcAB message;
    if(!capture.isOpened()){
        return -1;
    }

    while(capture.read(cameraFeed) && cv::waitKey(30) != ' ')
    {
        cv::imshow("Camera",cameraFeed);
        memcpy(&message.img, cameraFeed.data, sizeof(uint8_t) * IMG_SIZE);
        down(pqA->getSemid(), EMPTY);
        down(pqA->getSemid(), BIN);

        pqA->push(&message);

        up(pqA->getSemid(), BIN);
        up(pqA->getSemid(), FULL);
    }



}