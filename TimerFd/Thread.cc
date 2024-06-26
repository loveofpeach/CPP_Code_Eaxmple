#include "Thread.h"
#include <stdio.h>

Thread::Thread(ThreadCallback &&cb)
: _thid(0)
, _isRunning(false)
, _cb(std::move(cb))//注册回调函数
{
}

Thread::~Thread()
{
    if(_isRunning)
    {
        //让子线程与主线程分离，主线程不管子线程的回收
        pthread_detach(_thid);
        _isRunning = false;
    }
}

void Thread::start()
{
    int ret = pthread_create(&_thid, nullptr, threadFunc, this);
    if(ret)
    {
        perror("pthread_create\n");
        return;
    }

    _isRunning = true;
}

void Thread::join()
{
    if(_isRunning)
    {
        //shift + k(2, 3)
        int ret = pthread_join(_thid, nullptr);
        if(ret)
        {
            perror("pthread_join\n");
            return;
        }

        _isRunning = false;
    }
}

void *Thread::threadFunc(void *arg)
{
    Thread *pth1 = static_cast<Thread *>(arg);
    if(pth1)
    {
        pth1->_cb();//执行回调函数
    }

    pthread_exit(nullptr);
}

