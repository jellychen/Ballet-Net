#include "BalSignalCallbackPool.h"
using namespace Ballet;
using namespace Network;

BalSignalCallbackPool::BalSignalCallbackPool()
{

}

BalSignalCallbackPool::~BalSignalCallbackPool()
{

}

void BalSignalCallbackPool::ReceiveSignal(int signal, BalHandle<BalEventLoop> el)
{
    mapSignalCallbackPoolT::iterator iter = callbackPool_.find(signal);
    if (iter != callbackPool_.end())
    {
        BalHandle<IBalSignalCallback> callback = iter->second;
        if (callback && callback->IsCallable())
        {
            callback->OnReceiveSignal(signal, el);
        }
    }
}

bool BalSignalCallbackPool::AddSignalCallback(int signal, BalHandle<IBalSignalCallback> callback)
{
    if (!callback || !callback->IsCallable())
    {
        return false;
    }
    callbackPool_[signal] = callback;
    return true;
}

bool BalSignalCallbackPool::RemoveSignalCallback(int signal)
{
    mapSignalCallbackPoolT::iterator iter = callbackPool_.find(signal);
    if (callbackPool_.end() == iter) return false;
    callbackPool_.erase(iter);
    return true;
}
