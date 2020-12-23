#include "pqueue.hpp"
#include <vector>
#include <opencv2/opencv.hpp>
#define CVPLOT_HEADER_ONLY
#include <CvPlot/cvplot.h>
#include <fstream>


#define PLOT_WIDTH 800
#define PLOT_HEIGHT 400

int main() 
{
//    struct sched_param sp;
//    sp.sched_priority = 99;
//    sched_setscheduler(0, SCHED_FIFO, &sp);

    
    /*setSHM<ImageRaw>(PQ_A);
    setSHM<ProcessedValue>(PQ_B);*/

    std::cout<<"Initilizer running"<<std::endl;

    int semid_A = semget(SKEY_A, SEM_NUM, IPC_CREAT | 0600);
    int semid_B = semget(SKEY_B, SEM_NUM, IPC_CREAT | 0600);
    int semid_C = semget(SKEY_C, SEM_NUM, IPC_CREAT | 0600);
    int semid_D = semget(SKEY_D, SEM_NUM, IPC_CREAT | 0600);


    setSHM<ProcAB>(PQ_A); //queue A is created for communication beetwen process A(capture) and B(convert)
    setSHM<ProcBC>(PQ_B); //queue B is created for communication beetwen process B(convert) and C(draw)
    setSHM<ProcCD>(PQ_C); //queue C is created for communication beetwen process C(draw) and D(init)
    setSHM<ProcBD>(PQ_D); //queue D is created for communication beetwen process B(convert) and D(init)

    semctl(semid_A, FULL, SETVAL, (int)0);
    semctl(semid_B, FULL, SETVAL, (int)0);
    semctl(semid_C, FULL, SETVAL, (int)0);
    semctl(semid_D, FULL, SETVAL, (int)0);

    semctl(semid_A, EMPTY, SETVAL, (int)CAP);
    semctl(semid_B, EMPTY, SETVAL, (int)CAP);
    semctl(semid_C, EMPTY, SETVAL, (int)CAP);
    semctl(semid_D, EMPTY, SETVAL, (int)CAP);

    semctl(semid_A, BIN, SETVAL, (int)1);
    semctl(semid_B, BIN, SETVAL, (int)1);
    semctl(semid_C, BIN, SETVAL, (int)1);
    semctl(semid_D, BIN, SETVAL, (int)1);

    std::cout<<"Zainicjowano pamiec wspoldzielona\n";

    ProcCD m_inC; //times from draw
    ProcBD m_inB; //times from convert
    
    int shmidD = shmget(KEY_D, sizeof(PQueue<ProcBD>),0);
    PQueue<ProcBD> *pqD = (PQueue<ProcBD> *)shmat(shmidD, NULL, 0);

    int shmidC = shmget(KEY_C, sizeof(PQueue<ProcCD>), 0);
    PQueue<ProcCD> *pqC = (PQueue<ProcCD> *)shmat(shmidC, NULL, 0);

    std::vector<double> delay_AB;
    std::vector<double> delay_BC;
    std::vector<double> delay_BD;
    std::vector<double> delay_CD;

    //log files
    std::ofstream log("delays.log");

    std::cout << "PRESS SPACE TO EXIT" <<std::endl;
    int i = 0;
    while(1){
        down(pqD->getSemid(), FULL);
        down(pqD->getSemid(), BIN);        
        
        m_inB=pqD->pop();
        
        up(pqD->getSemid(), BIN);
        up(pqD->getSemid(), EMPTY);
        auto t = std::chrono::high_resolution_clock::now();

        auto ts_delay_BD = std::chrono::duration_cast<std::chrono::milliseconds>( t - m_inB.timestamp ).count();

        down(pqC->getSemid(), FULL);
        down(pqC->getSemid(), BIN);        
        
        m_inC=pqC->pop();
        
        up(pqC->getSemid(), BIN);
        up(pqC->getSemid(), EMPTY);
        t = std::chrono::high_resolution_clock::now();

        auto ts_delay_CD = std::chrono::duration_cast<std::chrono::milliseconds>( t - m_inC.timestamp ).count();

        if(i++ >= 100){
            delay_AB.push_back(m_inB.AB_delay);
            delay_BC.push_back(m_inC.BC_delay);
            delay_BD.push_back(ts_delay_BD);
            delay_CD.push_back(ts_delay_CD);
            log << m_inB.AB_delay << " " << m_inC.BC_delay << " " << ts_delay_BD << " " << ts_delay_CD << std::endl;
        }
        auto axesDelay = CvPlot::makePlotAxes();
        axesDelay.create<CvPlot::Series>(delay_AB, "-r");
        axesDelay.create<CvPlot::Series>(delay_BC, "-b");
        axesDelay.create<CvPlot::Series>(delay_BD, "-g");
        axesDelay.create<CvPlot::Series>(delay_CD, "-y");

        cv::Mat imgDelay = axesDelay.render(PLOT_HEIGHT, PLOT_WIDTH);
        cv::imshow("Delays", imgDelay);

        if(cv::waitKey(DELAY) == ' '){
            cv::imwrite("plots.png", imgDelay);
            break;
        }
    }

    return 0;
}
