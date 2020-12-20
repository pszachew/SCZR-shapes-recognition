#include "pqueue.hpp"

void setSemaphores() 
{
    int semid_A, semid_B, semid_C, semid_D;

    semid_A = semget(SKEY_A, SEM_NUM, IPC_CREAT | 0600);
    semid_B = semget(SKEY_B, SEM_NUM, IPC_CREAT | 0600);
    semid_C = semget(SKEY_C, SEM_NUM, IPC_CREAT | 0600);
    semid_D = semget(SKEY_D, SEM_NUM, IPC_CREAT | 0600);

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
}