#include "BalEventLoop.h"
using namespace Ballet::BootUtil;
using namespace Ballet::Network;

BalEventLoop::BalEventLoop()
    :eventDataManager_(MAX_EVENTDATA_CACHE)
    ,timer_(new BalTimer),doReadyPoolProtected_(false)
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
    if (!callback) return false;
    if (!(event & (EventRead | EventWrite))) return false;
    int fd = handle.GetFd(); if (0 >= fd) return false;

    if (!handle.IsWaitEvent())
    {
        struct epoll_event ev;
        memset(&ev, 0, sizeof(epoll_event));
        ev.data.fd = fd; ev.events = EPOLLET;
        ev.events |= ((event &EventRead)? EPOLLIN: 0);
        ev.events |= ((event &EventWrite)? EPOLLOUT: 0);

        BalEventData* eventData = eventDataManager_.GetOne();
        if (eventData)
        {
            eventData->fd_ = fd;
            ev.data.ptr = eventData;
            handle.eventData_ = eventData;
            eventData->callback_ = callback;
        }
        ::epoll_ctl(efd_, EPOLL_CTL_ADD, fd, &ev);
    }
    else
    {
        BalEventEnum eventStatus = handle.GetEventWaitStatus();
        eventStatus = (BalEventEnum)(eventStatus | event);

        struct epoll_event ev;
        memset(&ev, 0, sizeof(epoll_event));
        ev.data.fd = fd; ev.events = EPOLLET;
        ev.events |= ((event &EventRead)? EPOLLIN: 0);
        ev.events |= ((event &EventWrite)? EPOLLOUT: 0);

        BalEventData* eventData = handle.eventData_;
        if (eventData)
        {
            eventData->fd_ = fd;
            ev.data.ptr = eventData;
            eventData->callback_ = callback;
        }
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
        if (handle.eventData_)
        {
            RemoveReadyItem(handle.eventData_->index_, fd, statusChange);
        }

        struct epoll_event ev;
        memset(&ev, 0, sizeof(epoll_event));
        ev.data.fd = fd; ev.events = EPOLLET;
        if (EventNone == eventStatus)
        {
            ::epoll_ctl(efd_, EPOLL_CTL_DEL, fd, &ev);
            eventDataManager_.RevertBack(handle.eventData_);
            handle.eventData_ = nullptr_();
        }
        else
        {
            ev.events |= ((event &EventRead)? EPOLLIN: 0);
            ev.events |= ((event &EventWrite)? EPOLLOUT: 0);
            ::epoll_ctl(efd_, EPOLL_CTL_MOD, fd, &ev);
        }
    }
    return true;
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

bool BalEventLoop::DoEventSelect(int time)
{
    if (efd_ <= 0) return false;
    releaseList_.clear();

    struct epoll_event events[10240];
    int nfds = ::epoll_wait(efd_, events, 10240, time);
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
            if (eventData && eventData->callback_)
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

    BalHandle<BalEventLoop> eventLoop(this, shareUserCount_);
    DoReadyPool(eventLoop);
    return true;
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
        bool closed = false;
        BalEventReadyItem& item = readyPool_[i];
        if (!item.callback_ || !(item.callback_->IsCallable())) continue;
        BalEventCallbackEnum ret = EventRetNone;

        if (0 != item.write_)
        {
            ret = item.callback_->ShouldWrite(item.fd_, eventLoop);
            if (EventRetClose == ret)
            {
                closed = true;
            }
            else if (EventRetAgain == ret || EventRetComplete == ret)
            {
                item.write_ = 0;
            }
        }

        if (false == closed && 0 != item.read_)
        {
            ret = item.callback_->ShouldRead(item.fd_, eventLoop);
            if (EventRetClose == ret)
            {
                closed = true;
            }
            else if (EventRetAgain == ret || EventRetComplete == ret)
            {
                item.read_ = 0;
            }
        }

        if (closed || (0 == item.write_ && 0 == item.read_))
        {
            int lastItemIndex = len -1;
            if (i < lastItemIndex)
            {
                readyPool_[i].eventData_->index_ = -1;
                readyPool_[i].eventData_->index_ = i;
                readyPool_[i] = readyPool_[lastItemIndex];
            }
            else
            {
                readyPool_[i].eventData_->index_ = -1;
            }
            readyPool_[lastItemIndex].callback_.Clear();
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

    if (index < 0 || fd != readyPool_[index].fd_)
    {
        BalEventReadyItem item = {fd, 0, 0, data, callback};
        item.read_ = (ready &EventRead)? 1: 0;
        item.write_ = (ready &EventWrite)? 1: 0;
        readyPool_.push_back(item);
        index = (int)readyPool_.size() -1;
    }
    else
    {
        BalEventReadyItem& item = readyPool_[index];
        item.eventData_ = data;
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

    BalEventReadyItem& item = readyPool_[index];
    if (item.fd_ != fd) return false;
    item.read_ = (ready &EventRead)? 0: 1;
    item.write_ = (ready &EventWrite)? 0: 1;

    if (0 == item.read_ && 0 == item.write_ && !doReadyPoolProtected_)
    {
        size_t len = readyPool_.size() -1;
        if (index < len)
        {
            readyPool_[index].eventData_->index_ = -1;
            readyPool_[len].eventData_->index_ = index;
            readyPool_[index] = readyPool_[len];
        }
        else
        {
            readyPool_[len].eventData_->index_ = -1;
        }
        readyPool_[len].callback_.Clear();
        readyPool_.resize(len);
    }
    return true;
}
