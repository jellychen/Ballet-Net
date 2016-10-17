#include "BalTaskEventLoop.h"
using namespace Ballet;
using namespace Thread;
using namespace Network;

BalTaskEventLoop::BalTaskEventLoop()
    :eventFd_(::eventfd(0, EFD_NONBLOCK |FD_CLOEXEC)), event_(eventFd_)
    ,callback_(this)
{
    if (eventFd_ <= 0)
    {
        throw std::runtime_error("BalThreadPoolEventLoop Construct Failed!");
    }

    inQueue_ = queue_; outQueue_ = queue_ + 1;
    ::pthread_mutex_init(&queuelocker_, nullptr_());
    callback_->HookShouldRead(&BalTaskEventLoop::OnTask);
    SetEventListener(event_, EventRead, callback_);
}

BalTaskEventLoop::~BalTaskEventLoop()
{
    if (eventFd_ > 0)
    {
        ::close(eventFd_);
    }
    ::pthread_mutex_destroy(&queuelocker_);
}

void BalTaskEventLoop::DoTaskInThreadPool(BalThreadTask* task)
{
    Commit(task);
}

void BalTaskEventLoop::Commit(BalThreadTask* task)
{
    if (!task) return;
    ::pthread_mutex_lock(&queuelocker_);
    inQueue_->push(task);

    uint64_t _u = 1;
    ssize_t ret = ::write(eventFd_, &_u, sizeof(uint64_t)); if (ret) {}
    ::pthread_mutex_unlock(&queuelocker_);
}

void BalTaskEventLoop::ExecuteTaskInCurrentThread()
{
    taskQueueT* readQueue = nullptr_();
    ::pthread_mutex_lock(&queuelocker_);
    taskQueueT* temp = outQueue_;
    outQueue_ = inQueue_; inQueue_ = temp;
    readQueue = temp;
    ::pthread_mutex_unlock(&queuelocker_);

    if (readQueue)
    {
        while (readQueue->size() > 0)
        {
            BalThreadTask* task = readQueue->front();
            if (task) task->DoTask();
            readQueue->pop();
        }
    }
}

BalEventCallbackEnum BalTaskEventLoop::OnTask(int id, BalHandle<BalEventLoop> el)
{
    uint64_t _u;
    ssize_t ret = ::read(eventFd_, &_u, sizeof(uint64_t)); if (ret) {}
    ExecuteTaskInCurrentThread();
    return EventRetComplete;
}
