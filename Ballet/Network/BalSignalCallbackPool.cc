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
        mapCallbackT::iterator insideIter = iter->second.begin();
        for (; insideIter != iter->second.end();)
        {
            BalHandle<IBalSignalCallback> callback = insideIter->second;
            if (callback && callback->IsCallable())
            {
                ++insideIter;
                callback->OnReceiveSignal(signal, el);
            }
            else
            {
                iter->second.erase(insideIter++);
            }
        }

        if (0 == iter->second.size())
        {
            callbackPool_.erase(iter);
        }
    }
}

bool BalSignalCallbackPool::AddSignalCallback(int signal, BalHandle<IBalSignalCallback> callback)
{
    if (!callback || !callback->IsCallable()) return false;
    long hashCode = callback.HashCode();
    mapSignalCallbackPoolT::iterator iter = callbackPool_.find(signal);
    if (iter != callbackPool_.end())
    {
        iter->second[hashCode] = callback;
    }
    else
    {
        mapCallbackT callbackInsidePool;
        callbackInsidePool[hashCode] = callback;
        callbackPool_[signal] = callbackInsidePool;
    }
    return true;
}

bool BalSignalCallbackPool::RemoveSignalCallback(int signal, BalHandle<IBalSignalCallback> callback)
{
    if (!callback || !callback->IsCallable()) return false;
    mapSignalCallbackPoolT::iterator iter = callbackPool_.find(signal);
    if (callbackPool_.end() == iter) return false;
    long hashCode = callback.HashCode();
    mapCallbackT::iterator insideIter = iter->second.find(hashCode);
    if (iter->second.end() != insideIter)
    {
        iter->second.erase(insideIter);
        if (0 == iter->second.size())
        {
            callbackPool_.erase(iter);
        }
    }
    return true;
}
