#include "BalEventHandle.h"
using namespace Ballet;
using namespace Network;

BalEventHandle::BalEventHandle()
{
    BalEventHandle::Reset(0);
}

BalEventHandle::BalEventHandle(int fd)
{
    BalEventHandle::Reset(fd);

}

BalEventHandle::~BalEventHandle()
{
}

void BalEventHandle::Reset(int fd)
{
    eventData_.Reset();
    eventData_.fd_ = fd;
    eventStatus_ = EventNone;
}

int BalEventHandle::GetFd() const
{
    return eventData_.fd_;
}

bool BalEventHandle::IsWaitEvent() const
{
    return 0 != eventData_.fd_ && EventNone != eventStatus_;
}

void BalEventHandle::SetEventWaitStatus(BalEventEnum event)
{
    eventStatus_ = event;
}

BalEventEnum BalEventHandle::GetEventWaitStatus() const
{
    return eventStatus_;
}
