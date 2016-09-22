#include "BalEventHandle.h"
using namespace Ballet;
using namespace Network;

BalEventHandle::BalEventHandle(int fd)
{
    fd_ = fd;
    eventData_ = nullptr_();
    eventStatus_ = EventNone;
}

int BalEventHandle::GetFd() const
{
    return fd_;
}

bool BalEventHandle::IsWaitEvent() const
{
    return 0 != fd_ && EventNone != eventStatus_;
}

void BalEventHandle::SetEventWaitStatus(BalEventEnum event)
{
    eventStatus_ = event;
}

BalEventEnum BalEventHandle::GetEventWaitStatus() const
{
    return eventStatus_;
}
