#include "BalTaskThreadPool.h"
using namespace Ballet;
using namespace Thread;

BalTaskThreadPool::BalTaskThreadPool(uint32_t num)
{
    if (0 == num)
    {
        throw std::runtime_error("BalTaskThreadPool Construct Failed");
    }

    for (uint32_t i = 0; i < num; ++i)
    {
        pthread_t _t;
        pthread_attr_t _attr; ::pthread_attr_init(&_attr);
        int ret = ::pthread_create(&_t, &_attr,\
            BalTaskThreadPool::thread_function, (void*)(&taskThreadInfo_));
        ::pthread_attr_destroy(&_attr);
        if (0 == ret)
        {
            threadObjects_.push_back(_t);
        }
    }

    taskThreadInfo_.exit_ = false;
    ::pthread_cond_init(&(taskThreadInfo_.threadCond_), nullptr_());
    ::pthread_mutex_init(&(taskThreadInfo_.queuelocker_), nullptr_());
}

BalTaskThreadPool::~BalTaskThreadPool()
{
    taskThreadInfo_.exit_ = true;
    if (threadObjects_.size() > 0)
    {
        ::pthread_cond_broadcast(&(taskThreadInfo_.threadCond_));
        for (size_t i = 0; i < threadObjects_.size(); ++i)
        {
            ::pthread_join(threadObjects_[i], 0);
        }
    }
    ::pthread_cond_destroy(&(taskThreadInfo_.threadCond_));
    ::pthread_mutex_destroy(&(taskThreadInfo_.queuelocker_));
}

void* BalTaskThreadPool::thread_function(void* arg)
{
    taskThreadInfoT* info = (taskThreadInfoT*)(arg);
    while (info)
    {
        bool exitLoop = false;
        BalThreadTask* task = nullptr_();
        ::pthread_mutex_lock(&(info->queuelocker_));
        if (info->queue_.size() <= 0 && !(info->exit_))
        {
            ::pthread_cond_wait(&(info->threadCond_), &(info->queuelocker_));
        }
        exitLoop = info->exit_;

        if (!exitLoop)
        {
            task = info->queue_.front();
            info->queue_.pop();
        }
        ::pthread_mutex_unlock(&(info->queuelocker_));

        if (task)
        {
            task->DoTask();
        }
        if (exitLoop) break;
    }
}

void BalTaskThreadPool::Commit(BalThreadTask* task)
{
    if (!task) return;
    ::pthread_mutex_lock(&(taskThreadInfo_.queuelocker_));
    taskThreadInfo_.queue_.push(task);
    ::pthread_cond_signal(&(taskThreadInfo_.threadCond_));
    ::pthread_mutex_unlock(&(taskThreadInfo_.queuelocker_));
}
