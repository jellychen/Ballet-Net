#include "BalEventLoop.h"
using namespace Ballet;
using namespace Network;

BalEventLoop::BalEventLoop():efd_(0),created_(false)
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

bool BalEventLoop::SetEventListener(int id, BalEventEnum event, BalEventCallback& callback)
{
    if (efd_ <= 0 || id <= 0 || !callback) return false;
    if (!(event & (EventRead | EventWrite))) return false;

    mapEventPoolT::iterator iter = eventPool_.find(id);
    if (eventPool_.end() == iter)
    {
        BalEventCallbackWrapper cb = {callback, EPOLLET, -1};
        cb.status_ |= (event &EventRead)? EPOLLIN: 0;
        cb.status_ |= (event &EventWrite)? EPOLLOUT: 0;

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
        if (0 != ::epoll_ctl(efd_, EPOLL_CTL_DEL, id, &ev)) return false;
        eventPool_.erase(iter);
    }
    else
    {
        if (0 != ::epoll_ctl(efd_, EPOLL_CTL_MOD, id, &ev)) return false;
        iter->second.status_ = ev.events;
    }
    return true;
}
