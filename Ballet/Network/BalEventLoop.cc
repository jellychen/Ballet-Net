#include "BalEventLoop.h"
using namespace Ballet;
using namespace Network;

BalEventLoop::BalEventLoop()
{

}

BalEventLoop::~BalEventLoop()
{

}

bool BalEventLoop::Init() throw()
{
    return true;
}

bool BalEventLoop::AddDelayReleaseElement(BalHandle<BalElement>&)
{
    return true;
}

bool BalEventLoop::DeleteEventListener(int id, BalEventEnum event)
{
    return true;
}

bool BalEventLoop::SetEventListener(int id, BalEventEnum event, BalHandle<IBalEventCallback>&)
{
    return true;
}
