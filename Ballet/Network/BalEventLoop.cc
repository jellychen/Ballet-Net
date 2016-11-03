#include "BalEventLoop.h"
using namespace Ballet::BootUtil;
using namespace Ballet::Network;

BalEventLoop::BalEventLoop()
    :timer_(new BalTimer), doReadyPoolProtected_(false)
    ,maintenanceSignal_(false)
{
    efd_ = ::epoll_create1(EPOLL_CLOEXEC);
    if (0 == efd_)
    {
        throw std::runtime_error("BalEventLoop Construct Failed! @1");
    }
}

BalEventLoop::~BalEventLoop()
{
    if (0 != efd_)
    {
        ::close(efd_);
    }

    if (0 != sfd_)
    {
        ::close(sfd_);
    }
}

bool BalEventLoop::AddDelayReleaseElement(BalHandle<BalElement>& element)
{
    releaseList_.push_back(element);
    return true;
}

bool BalEventLoop::AddHoldSomeElement(long id, BalHandle<BalElement>& element)
{
    if (!element) return false;
    mapHoldPoolT::iterator iter = holdElementPool_.find(id);
    if (iter != holdElementPool_.end()) return false;
    holdElementPool_[id] = element;
    return true;
}

bool BalEventLoop::RemoveHoldElement(long id)
{
    mapHoldPoolT::iterator iter = holdElementPool_.find(id);
    if (iter == holdElementPool_.end()) return false;
    holdElementPool_.erase(iter);
    return true;
}

bool BalEventLoop::SetEventListener(
    BalEventHandle& handle, BalEventEnum event, BalEventCallback callback)
{
    if (!(event & (EventRead | EventWrite))) return false;
    int fd = handle.GetFd(); if (0 >= fd) return false;
    if (!callback || !(callback->IsCallable())) return false;
    
    if (!handle.IsWaitEvent())
    {
        struct epoll_event ev;
        memset(&ev, 0, sizeof(epoll_event));
        ev.events = EPOLLET;
        ev.events |= ((event &EventRead)? EPOLLIN: 0);
        ev.events |= ((event &EventWrite)? EPOLLOUT: 0);

        BalEventData* eventData = &(handle.eventData_);
        eventData->fd_ = fd;
        eventData->callback_ = callback;
        ev.data.ptr = eventData;
        handle.eventStatus_ = event;
        handle.eventData_.needDelEvent_ = true;

        ::epoll_ctl(efd_, EPOLL_CTL_ADD, fd, &ev);
    }
    else
    {
        BalEventEnum eventStatus = handle.GetEventWaitStatus();
        BalEventEnum eventNewStatus = (BalEventEnum)(eventStatus | event);
        if (eventStatus == eventNewStatus) return true;

        struct epoll_event ev;
        memset(&ev, 0, sizeof(epoll_event));
        ev.events = EPOLLET;
        ev.events |= ((event &EventRead)? EPOLLIN: 0);
        ev.events |= ((event &EventWrite)? EPOLLOUT: 0);

        BalEventData* eventData = &(handle.eventData_);
        eventData->fd_ = fd;
        eventData->callback_ = callback;
        ev.data.ptr = eventData;
        handle.eventStatus_ = eventNewStatus;
        handle.eventData_.needDelEvent_ = true;

        ::epoll_ctl(efd_, EPOLL_CTL_MOD, fd, &ev);
    }
    return true;
}

bool BalEventLoop::DeleteEventListener(BalEventHandle& handle, BalEventEnum event)
{
    if (!(event & (EventRead | EventWrite))) return false;
    int fd = handle.GetFd(); if (0 >= fd) return false;
    if (!handle.IsWaitEvent()) return false;

    BalEventEnum eventStatus = handle.GetEventWaitStatus();
    BalEventEnum statusChange = EventNone;
    if ((eventStatus & EventRead) && (event & EventRead))
    {
        eventStatus = (BalEventEnum)(eventStatus &~ EventRead);
        statusChange = (BalEventEnum)(statusChange | EventRead);
    }

    if ((eventStatus & EventWrite) && (event & EventWrite))
    {
        eventStatus = (BalEventEnum)(eventStatus &~ EventWrite);
        statusChange = (BalEventEnum)(statusChange | EventWrite);
    }

    if (EventNone != statusChange)
    {
        RemoveReadyItem(handle.eventData_.index_, fd, statusChange);

        struct epoll_event ev;
        memset(&ev, 0, sizeof(epoll_event));
        ev.data.fd = fd; ev.events = EPOLLET;
        handle.eventStatus_ = eventStatus;

        if (EventNone == eventStatus)
        {
            handle.eventData_.needDelEvent_ = false;
            ::epoll_ctl(efd_, EPOLL_CTL_DEL, fd, &ev);
        }
        else
        {
            ev.events |= ((eventStatus &EventRead)? EPOLLIN: 0);
            ev.events |= ((eventStatus &EventWrite)? EPOLLOUT: 0);
            ::epoll_ctl(efd_, EPOLL_CTL_MOD, fd, &ev);
        }
    }
    return true;
}

bool BalEventLoop::SetSignalListener(int id, BalSignalCallback callback)
{
    if (!SetMaintenanceSignal()) return false;
    return signalCallbackPool_.AddSignalCallback(id, callback);
}

bool BalEventLoop::DeleteSignalListener(int id)
{
    return signalCallbackPool_.RemoveSignalCallback(id);
}

bool BalEventLoop::SetTimerOut(int id, BalTimerCallback callback, uint32_t time)
{
    return timer_->SetTimerOut(id, callback, time);
}

bool BalEventLoop::SetTimerLoop(int id, BalTimerCallback callback, uint32_t time)
{
    return timer_->SetTimerLoop(id, callback, time);
}

bool BalEventLoop::RemoveTimer(int id, BalTimerCallback callback)
{
    return timer_->RemoveTimer(id, callback);
}

bool BalEventLoop::DoEventSelect(int timeout)
{
    if (efd_ <= 0) return false;
    releaseList_.clear();
    struct epoll_event events[10240];
    int nfds = ::epoll_wait(efd_, events, 10240, timeout);
    BalHandle<BalEventLoop> eventLoop(this, shareUserCount_);

    timer_->Tick();

    if (-1 == nfds && errno == EINTR)
    {
        errno = 0;
    }
    else
    {
        for (int i = 0; i < nfds; ++i)
        {
            BalEventData* eventData = (BalEventData*)(events[i].data.ptr);
            if (sfd_ == eventData->fd_)
            {
                struct signalfd_siginfo fdsi;
                ssize_t len = ::read(sfd_, &fdsi, sizeof(struct signalfd_siginfo));
                if (len == sizeof(struct signalfd_siginfo))
                {
                    signalCallbackPool_.ReceiveSignal(fdsi.ssi_signo, eventLoop);
                }
            }
            else if (eventData && eventData->callback_)
            {
                BalEventEnum eventStatus = EventNone;
                if (events[i].events &EPOLLIN)
                {
                    eventStatus = (BalEventEnum)(eventStatus |EventRead);
                }

                if (events[i].events &EPOLLOUT)
                {
                    eventStatus = (BalEventEnum)(eventStatus |EventWrite);
                }

                if (EventNone != eventStatus)
                {
                    eventData->index_ = AddReadyItem(eventData->index_,
                        eventData->fd_, eventStatus, eventData->callback_, eventData);
                }
            }
        }
    }

    return DoReadyPool(eventLoop);
}

bool BalEventLoop::DoEventLoop()
{
    shouldExit_ = false;
    while (true)
    {
        if (readyPool_.size() > 0)
        {
            DoEventSelect(0);
        }
        else
        {
            DoEventSelect((int)timer_->LastestTimeout());
        }

        if (shouldExit_)
        {
             break;
        }
    }
    return true;
}

bool BalEventLoop::DoExitEventLoop()
{
    shouldExit_ = true;
    return true;
}

bool BalEventLoop::DoReadyPool(BalHandle<BalEventLoop> eventLoop)
{
    if (!eventLoop || 0 == readyPool_.size()) return false;

    doReadyPoolProtected_ = true;
    bool resize = false;
    int32_t len = (uint32_t)readyPool_.size();
    for (int32_t i = 0; i < len;)
    {
        bool needRemove = false;
        BalEventReadyItem& item = readyPool_[i];
        if (!item.callback_ || !(item.callback_->IsCallable()))
        {
            needRemove = true;
        }
        BalEventCallbackEnum ret = EventRetNone;

        if (false == needRemove && 0 != item.write_)
        {
            ret = item.callback_->ShouldWrite(item.fd_, eventLoop);
            if (EventRetClose == ret)
            {
                needRemove = true;
            }
            else if (EventRetAgain == ret || EventRetComplete == ret)
            {
                item.write_ = 0;
            }
        }

        if (false == needRemove && 0 != item.read_)
        {
            ret = item.callback_->ShouldRead(item.fd_, eventLoop);
            if (EventRetClose == ret)
            {
                needRemove = true;
            }
            else if (EventRetAgain == ret || EventRetComplete == ret)
            {
                item.read_ = 0;
            }
        }

        if (needRemove || (0 == item.write_ && 0 == item.read_))
        {
            int lastItemIndex = len -1;
            if (i < lastItemIndex)
            {
                readyPool_[i].eventData_->index_ = -1;
                readyPool_[i] = readyPool_[lastItemIndex];
                readyPool_[lastItemIndex].callback_.Clear();
                readyPool_[lastItemIndex].eventData_ = nullptr_();
                readyPool_[i].eventData_->index_ = i;
            }
            else
            {
                readyPool_[i].callback_.Clear();
                readyPool_[i].eventData_->index_ = -1;
                readyPool_[i].eventData_ = nullptr_();
            }
            --len; resize = true;
        }
        else
        {
            ++i;
        }
    }

    if (true == resize)
    {
        readyPool_.resize(len);
    }
    doReadyPoolProtected_ = false;

    return true;
}

int BalEventLoop::AddReadyItem(int index, int fd,
        BalEventEnum ready, BalEventCallback& callback, BalEventData* data)
{
    if (fd <= 0 || !callback || !callback->IsCallable() || !data)
    {
        return false;
    }

    if (index < 0)
    {
        BalEventReadyItem item = {fd, 0, 0, data, callback};
        item.read_ = (ready &EventRead)? 1: 0;
        item.write_ = (ready &EventWrite)? 1: 0;
        readyPool_.push_back(item);
        index = (int)readyPool_.size() -1;
    }
    else
    {
        if (index >= (int)readyPool_.size() || fd != readyPool_[index].fd_)
        {
            throw std::runtime_error("AddReadyItem Error!");
        }

        BalEventReadyItem& item = readyPool_[index];
        item.callback_ = callback;
        item.read_ = (ready &EventRead)? 1: 0;
        item.write_ = (ready &EventWrite)? 1: 0;
    }
    return index;
}

bool BalEventLoop::RemoveReadyItem(int index, int fd, BalEventEnum ready)
{
    if (index < 0 || index >= (int)readyPool_.size())
    {
        return false;
    }
    if (doReadyPoolProtected_) return false;

    BalEventReadyItem& item = readyPool_[index];
    if (item.fd_ != fd)
    {
        throw std::runtime_error("RemoveReadyItem Error!");
    }
    item.read_ = (ready &EventRead)? 0: 1;
    item.write_ = (ready &EventWrite)? 0: 1;

    if (0 == item.read_ && 0 == item.write_)
    {
        size_t len = readyPool_.size() -1;
        if (index < len)
        {
            readyPool_[index].eventData_->index_ = -1;
            readyPool_[index].eventData_ = nullptr_();
            readyPool_[index] = readyPool_[len];
            readyPool_[index].eventData_->index_ = index;
            readyPool_[len].callback_.Clear();
            readyPool_[len].eventData_ = nullptr_();
        }
        else
        {
            readyPool_[len].eventData_->index_ = -1;
            readyPool_[len].eventData_ = nullptr_();
            readyPool_[len].callback_.Clear();
        }

        readyPool_.resize(len);
    }
    return true;
}

bool BalEventLoop::SetMaintenanceSignal()
{
    if (maintenanceSignal_)
    {
        return true;
    }

    bool success = false;

    do
    {
        sigset_t signalMask;
        if (0 > ::sigfillset(&signalMask)) break;
        if (0 > ::sigprocmask(SIG_BLOCK, &signalMask, 0)) break;
        sfd_ = ::signalfd(-1, &signalMask, 0);
        if (0 >= sfd_) break;
        if (0 != ::fcntl(sfd_, F_SETFL,
            ::fcntl(sfd_, F_GETFL)|O_NONBLOCK|FD_CLOEXEC)) break;

        struct epoll_event singalev;
        memset(&singalev, 0, sizeof(epoll_event));
        BalEventData* eventData = new(std::nothrow)BalEventData();
        if (!eventData) break; eventData->fd_ = sfd_;
        singalev.events = EPOLLIN; singalev.data.ptr = eventData;
        if (0 != ::epoll_ctl(efd_, EPOLL_CTL_ADD, sfd_, &singalev)) break;
        success = true;
    } while(0);
    maintenanceSignal_ = true;
    return success;
}
