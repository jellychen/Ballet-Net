#include "BalTimerHeap.h"
using namespace Ballet::BootUtil;

BalTimeHeap::BalTimeHeap()
{
    cacheInfo_ = 10000;
    BalTimerNode node = {nullptr_(), 0, 0};
    heapArray_.push_back(node);
}

BalTimeHeap::~BalTimeHeap()
{

}

bool BalTimeHeap::TickTimer()
{
    return true;
}

bool BalTimeHeap::SetTimerOut(int id, BalTimerCallback& callback, uint32_t time)
{
    return BalTimeHeap::SetTimerNode(id, callback, time, false);
}

bool BalTimeHeap::SetTimerLoop(int id, BalTimerCallback& callback, uint32_t time)
{
    return BalTimeHeap::SetTimerNode(id, callback, time, true);
}

bool BalTimeHeap::RemoveTimer(int id, BalTimerCallback& callback)
{
    return true;
}

int64_t BalTimeHeap::LastestTimeout() const
{
    if (1 >= heapArray_.size())
    {
        return INT_MAX;
    }
    int64_t time = heapArray_[1].timeout_ - timestamp_.Current();
    return time > 0 ?time :0;
}

bool BalTimeHeap::AddTimerNode(BalTimerNode& node)
{
    return true;
}

bool BalTimeHeap::RemoveTimerNode(uint32_t index)
{
    return true;
}

bool BalTimeHeap::SetTimerNode(int id, BalTimerCallback& callback, uint32_t time, bool loop)
{
    return true;
}
