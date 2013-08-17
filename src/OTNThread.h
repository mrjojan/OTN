#ifndef OTNTHREAD_H
#define OTNTHREAD_H

#include <pthread.h>
#include <iostream>

class OTNThread 
{
    public:
        void start();
    public:
        virtual void execute();
    public:
        void wait_for_exit();
    private:
        pthread_t handle;
};

#endif
