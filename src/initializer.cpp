#include "pqueue.hpp"

int main() 
{
//    struct sched_param sp;
//    sp.sched_priority = 99;
//    sched_setscheduler(0, SCHED_FIFO, &sp);

    
    /*setSHM<ImageRaw>(PQ_A);
    setSHM<ProcessedValue>(PQ_B);*/

    std::cout<<"init"<<std::endl;

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

    std::cout<<"\nZainicjowano pamiec wspoldzielona\n";

    ProcCD m_inC; //times from draw
    ProcBD m_inB; //times from convert
    
    int shmidD = shmget(KEY_D, sizeof(PQueue<ProcBD>),0);
    PQueue<ProcBD> *pqD = (PQueue<ProcBD> *)shmat(shmidD, NULL, 0);

    int shmidC = shmget(KEY_C, sizeof(PQueue<ProcCD>), 0);
    PQueue<ProcCD> *pqC = (PQueue<ProcCD> *)shmat(shmidC, NULL, 0);


    while(1){
        down(pqD->getSemid(), FULL);
        down(pqD->getSemid(), BIN);        
        
        m_inB=pqD->pop();
        
        up(pqD->getSemid(), BIN);
        up(pqD->getSemid(), EMPTY);

        

        down(pqC->getSemid(), FULL);
        down(pqC->getSemid(), BIN);        
        
        m_inC=pqC->pop();
        
        up(pqC->getSemid(), BIN);
        up(pqC->getSemid(), EMPTY);
    }

    return 0;
}
