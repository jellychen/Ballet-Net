#include "BalEventLoop.h"
using namespace Ballet::BootUtil;
using namespace Ballet::Network;

BalEventLoop::BalEventLoop()
    :efd_(0),created_(false),timer_(new BalTimer),doReadyPoolProtected_(false)
{
}

BalEventLoop::~BalEventLoop()
{
    if (0 != efd_)
    {
        ::close(efd_);
    }
}

bool BalEventLoop::Create() throw()
{
    if (false == created_)
    {
        efd_ = ::epoll_create(256);
        created_ = true;
    }
    return 0 != efd_;
}

bool BalEventLoop::AddDelayReleaseElement(BalHandle<BalElement>& element)
{
    releaseList_.push_back(element);
    return true;
}

bool BalEventLoop::SetEventListener(int id, BalEventEnum event, BalEventCallback callback)
{
    if (efd_ <= 0 || id <= 0 || !callback) return false;
    if (!(event & (EventRead | EventWrite))) return false;

    mapEventPoolT::iterator iter = eventPool_.find(id);
    if (eventPool_.end() == iter)
    {
        BalEventCallbackWrapper cb = {callback, -1, EPOLLET};
        cb.status_ |= (event &EventRead)? EPOLLIN: 0;
        cb.status_ |= (event &EventWrite)? EPOLLOUT: 0;
        if (EPOLLET == cb.status_) return false;

        struct epoll_event ev;
        memset(&ev, 0, sizeof(epoll_event));
        ev.data.fd = id; ev.events = cb.status_;
        if (0 != ::epoll_ctl(efd_, EPOLL_CTL_ADD, id, &ev)) return false;
        eventPool_[id] = cb;
    }
    else
    {
        struct epoll_event ev;
        memset(&ev, 0, sizeof(epoll_event));
        ev.data.fd = id; ev.events = iter->second.status_;

        bool statusChange = false;
        if ((!(ev.events &EPOLLIN)) && (event &EventRead))
        {
            ev.events |= EPOLLIN; statusChange = true;
        }
        if ((!(ev.events & EPOLLOUT)) && (event &EventWrite))
        {
            ev.events |= EPOLLOUT; statusChange = true;
        }
        if (false == statusChange) return true;
        if (0 != ::epoll_ctl(efd_, EPOLL_CTL_MOD, id, &ev)) return false;
        iter->second.status_ = ev.events;
    }
    return true;
}

bool BalEventLoop::DeleteEventListener(int id, BalEventEnum event)
{
    if (efd_ <= 0 || id <= 0) return false;
    if (!(event & (EventRead | EventWrite))) return false;

    mapEventPoolT::iterator iter = eventPool_.find(id);
    if (eventPool_.end() == iter) false;
    struct epoll_event ev;
    memset(&ev, 0, sizeof(epoll_event));
    ev.data.fd = id; ev.events = iter->second.status_;

    uint8_t statusChange = 0;
    if ((ev.events &EPOLLIN) && (event &EventRead))
    {
        statusChange |= EventRead; ev.events &= ~EPOLLIN;
    }
    if ((ev.events &EPOLLOUT) && (event &EventWrite))
    {
        statusChange |= EventWrite; ev.events &= ~EPOLLOUT;
    }
    if (0 == statusChange) return true;

    if (0 == ev.events || EPOLLET == ev.events)
    {
        ::epoll_ctl(efd_, EPOLL_CTL_DEL, id, &ev);
        RemoveReadyItem(iter->second.index_, id, statusChange);
        eventPool_.erase(iter);
    }
    else
    {
        ::epoll_ctl(efd_, EPOLL_CTL_MOD, id, &ev);
        RemoveReadyItem(iter->second.index_, id, statusChange);
        iter->second.status_ = ev.events;
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
    releaseList_.clear();
    BalHandle<BalEventLoop> eventLoop(this, shareUserCount_);
    DoReadyPool(eventLoop); if (efd_ <= 0) return false;
    const static int MAX_READ_FD = 10240;
    struct epoll_event events[MAX_READ_FD];
    int nfds = ::epoll_wait(efd_, events, MAX_READ_FD, time);

    timer_->Tick();

    for (int i = 0; i < nfds; ++i)
    {
        mapEventPoolT::iterator iter = eventPool_.find(events[i].data.fd);
        if (eventPool_.end() == iter) continue;
        BalEventCallbackWrapper& callback = iter->second;

        if (events[i].events &EPOLLIN)
        {
            callback.index_ = AddReadyItem(callback.index_,
                events[i].data.fd, EventRead, callback.callback_, iter);
        }

        if (events[i].events &EPOLLOUT)
        {
            callback.index_ = AddReadyItem(callback.index_,
                events[i].data.fd, EventWrite, callback.callback_, iter);
        }
    }
    return true;
}

bool BalEventLoop::DoEventLoop()
{
    shouldExit_ = false;
    while (true)
    {
        DoEventSelect((int)timer_->LastestTimeout());
        if (shouldExit_) break;
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
    if (!eventLoop) return false;

    doReadyPoolProtected_ = true;
    size_t len = readyPool_.size() -1;
    for (size_t i = 0; i <= len;)
    {
        bool closed = false;
        BalEventReadyItem& item = readyPool_[i];
        if (!item.callback_ || !item.callback_->IsCallable()) continue;
        BalEventCallbackEnum ret = EventRetNone;

        if (0 != item.read_)
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

        if (false == close && 0 != item.write_)
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

        if (close || (0 == item.write_ && 0 == item.read_))
        {
            if (i < len)
            {
                readyPool_[i].iter_->second.index_ = -1;
                readyPool_[i] = readyPool_[len];
                readyPool_[i].iter_->second.index_ = i;
            }
            else
            {
                readyPool_[len].iter_->second.index_ = -1;
            }
            readyPool_[len].callback_.Clear();
            readyPool_.resize(len); --len;
        }
        else
        {
            ++i;
        }
    }
    doReadyPoolProtected_ = false;
    return true;
}

int BalEventLoop::AddReadyItem(int index, int id,
        int ready, BalEventCallback& callback, mapEventPoolT::iterator iter)
{
    if (id <= 0 || !callback || !callback->IsCallable() || iter == eventPool_.end())
    {
        return false;
    }

    if (index < 0 || id != readyPool_[index].fd_)
    {
        BalEventReadyItem item = {id, 0, 0, callback, iter};
        item.read_ = (ready &EventRead)? 1: 0;
        item.write_ = (ready &EventWrite)? 1: 0;
        readyPool_.push_back(item); index = (int)readyPool_.size() -1;
    }
    else
    {
        BalEventReadyItem& item = readyPool_[index];
        item.iter_ = iter; item.callback_ = callback;
        item.read_ |= (ready &EventRead)? 1: 0;
        item.write_ |= (ready &EventWrite)? 1: 0;
    }
    return index;
}

bool BalEventLoop::RemoveReadyItem(int index, int id, int ready)
{
    if (index < 0 || index >= (int)eventPool_.size())
    {
        return false;
    }

    BalEventReadyItem& item = readyPool_[index];
    if (item.fd_ != id) return false;
    item.read_ = (ready &EventRead)? 0: 1;
    item.write_ = (ready &EventWrite)? 0: 1;
    if (0 == item.read_ && 0 == item.write_ && !doReadyPoolProtected_)
    {
        size_t len = readyPool_.size() -1;
        if (index < len)
        {
            readyPool_[index].iter_->second.index_ = -1;
            readyPool_[len].iter_->second.index_ = index;
            readyPool_[index] = readyPool_[len];
        }
        else
        {
            readyPool_[len].iter_->second.index_ = -1;
        }
        readyPool_[len].callback_.Clear(); readyPool_.resize(len);
    }
    return true;
}
