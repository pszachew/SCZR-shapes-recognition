#include "pqueue.hpp"

int main() 
{
    int shmidA = shmget(KEY_A, sizeof(PQueue<ProcAB>), 0);
    int shmidB = shmget(KEY_B, sizeof(PQueue<ProcBC>), 0);
    int shmidC = shmget(KEY_C, sizeof(PQueue<ProcCD>), 0);
    int shmidD = shmget(KEY_D, sizeof(PQueue<ProcBD>), 0);
    
    PQueue<ProcAB> *pqA = (PQueue<ProcAB> *)shmat(shmidA, NULL, 0);
    PQueue<ProcBC> *pqB = (PQueue<ProcBC> *)shmat(shmidB, NULL, 0);
    PQueue<ProcCD> *pqC = (PQueue<ProcCD> *)shmat(shmidC, NULL, 0);
    PQueue<ProcBD> *pqD = (PQueue<ProcBD> *)shmat(shmidD, NULL, 0);

    shmctl(KEY_A, IPC_RMID, NULL);
    shmctl(KEY_B, IPC_RMID, NULL);
    shmctl(KEY_C, IPC_RMID, NULL);
    shmctl(KEY_D, IPC_RMID, NULL);


    shmctl(SKEY_A, IPC_RMID, NULL);
    shmctl(SKEY_B, IPC_RMID, NULL);
    shmctl(SKEY_C, IPC_RMID, NULL);
    shmctl(SKEY_D, IPC_RMID, NULL);

    semctl(pqA->getSemid(), FULL, IPC_RMID);
    semctl(pqB->getSemid(), FULL, IPC_RMID);
    semctl(pqC->getSemid(), FULL, IPC_RMID);
    semctl(pqD->getSemid(), FULL, IPC_RMID);

    semctl(pqA->getSemid(), EMPTY, IPC_RMID);
    semctl(pqB->getSemid(), EMPTY, IPC_RMID);
    semctl(pqC->getSemid(), EMPTY, IPC_RMID);
    semctl(pqD->getSemid(), EMPTY, IPC_RMID);

    semctl(pqA->getSemid(), BIN, IPC_RMID);
    semctl(pqB->getSemid(), BIN, IPC_RMID);
    semctl(pqC->getSemid(), BIN, IPC_RMID);
    semctl(pqD->getSemid(), BIN, IPC_RMID);

    return 0;
}
