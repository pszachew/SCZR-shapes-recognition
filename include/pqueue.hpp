#pragma once

#include <sys/shm.h>
#include <sched.h>
#include <unistd.h>

#include "message.hpp"
#include "semaphoreop.hpp"

#define CAP 100
#define SEM_NUM 3 /* semaphores per queue */
#define PQ_A 'A'
#define PQ_B 'B'
#define PQ_C 'C'
#define PQ_D 'D'
#define KEY_A 45281
#define KEY_B 45282
#define KEY_C 45283
#define KEY_D 45284

#define SKEY_A 45285
#define SKEY_B 45286
#define SKEY_C 45287
#define SKEY_D 45288

#define EMPTY 0
#define FULL 1
#define BIN 2

template <typename T> class PQueue
{
    private:
        int semid;
        char name;
        int bufSize;
        T buf[CAP];
    
    public:
        PQueue() {};
        ~PQueue() {};

    bool push(T *m)
    {
        this->buf[this->bufSize] = *m;
        (this->bufSize)++;
        return true;
    }

    T pop()
    {
        T m;

            if (this->bufSize==0)
            {

            }
            else
            {
                m=this->buf[0];
                if (this->bufSize==1) 
                {
                    this->bufSize=0;
                }
                else
                {
                    for (int index=0; index<this->bufSize-1; ++index)
                    {
                        this->buf[index]=this->buf[index+1];
                    }
                    --this->bufSize;
                }
            }

        return m;     
    }

    int getSemid() 
    {
        return this->semid;
    }

    char getName() 
    {
        return this->name;
    }

    int getSize() 
    {
        return this->bufSize;
    }

    void setSemid(int semid) 
    {
        this->semid = semid;
    }

    void setName(char name) 
    {
        this->name = name;
    }

    void setSize(int bufSize) 
    {
        this->bufSize = bufSize;
    }


};

template <typename T> PQueue<T> *setSHM(char group)
{
    PQueue<T> *pq = NULL;

    int shmid = 0;
    int semid = 0;
    int GROUP_KEY = 0;
    int SEM_KEY = 0;

    if (PQ_A == group) 
    {
        GROUP_KEY = KEY_A;
        SEM_KEY = SKEY_A;
    } 
    else if (PQ_B == group) 
    {
        GROUP_KEY = KEY_B;
        SEM_KEY = SKEY_B;
    }
    else if (PQ_C == group)
    {
        GROUP_KEY = KEY_C;
        SEM_KEY = SKEY_C;
    }
    else if (PQ_D == group)
    {
        GROUP_KEY = KEY_D;
        SEM_KEY = SKEY_D;
    }
    else
    {
        std::cout << "Wrong group name!\n";
        exit(1);
    }

    semid = semget(SEM_KEY, SEM_NUM, IPC_CREAT | 0600);
    shmid = shmget(GROUP_KEY, sizeof(PQueue<T>), IPC_CREAT | 0600);

    pq = (PQueue<T> *)shmat(shmid, NULL, 0);

    pq->setSemid(semid);
    pq->setName(group);
    pq->setSize(0);

    return pq;

}

