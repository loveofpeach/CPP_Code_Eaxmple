#ifndef _TASKQUEUE_H_
#define _TASKQUEUE_H_

#include "MutexLock.h"
#include "Condition.h"
#include <queue>
#include <functional>

using std::queue;
using std::function;
using ElemType = function<void()>;

class TaskQueue
{
public:
    TaskQueue(size_t queSize);
    ~TaskQueue();
    bool empty() const;
    bool full() const;
    void push(ElemType&& value);
    ElemType pop();

    // 唤醒所有等待在 notEmpty 条件变量上的线程
    void notify_notEmpty_all();

private:
    size_t _queSize;
    queue<ElemType> _que;
    MutexLock _mutex;
    Condition _notEmpty;
    Condition _notFull;
    bool _flag; // 标志位，让唤醒的线程退出
};

#endif