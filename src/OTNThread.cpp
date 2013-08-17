#include "OTNThread.h"

extern "C"
{
    // This C function will be used to receive the thread and pass it back to the Thread instance
    void* thread_catch(void* arg) 
    {
        OTNThread* t = static_cast<OTNThread*>(arg);
        t->execute();
        return 0;
    }
}

// method which starts the new thread
void OTNThread::start() 
{
    pthread_create(&handle, 0, thread_catch, this);
}

// code which will be run on the new thread
void OTNThread::execute() 
{
    std::clog << "Thread:Hello From a new Thread!" << std::endl;
}

// wait until this thread has finished executing
void OTNThread::wait_for_exit() 
{
    pthread_join(handle, NULL);
}
