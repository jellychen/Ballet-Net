#include "BalNetDefine.h"
#include "BalTcpServer.h"
using namespace Ballet;
using namespace Network;

BalTcpServer::BalTcpServer(bool v6, BalHandle<BalEventLoop> eventLoop,
    BalHandle<IBalTcpCallback> callback, uint32_t timeout, uint32_t maxReadBufferSize,
    uint32_t maxWriteBufferSize):BalTcpSocket(v6),eventCallbackPtr_(this)
{
    eventLoop_ = eventLoop;
    maxReadBufferSize_ = maxReadBufferSize;
    maxWriteBufferSize_ = maxWriteBufferSize;
    if (!callback || !callback->IsCallable())
    {
        throw std::runtime_error("BalTcpServer Construct Failed");
    }
    else
    {
        tcpCallback_ = callback;
    }

    if (!eventLoop_ || !eventCallbackPtr_ || !Listen() || !SetNoBlock())
    {
        throw std::runtime_error("BalTcpServer Construct Failed");
    }
    else
    {
        eventCallbackPtr_->HookShouldRead(&BalTcpServer::ShoudAccept);
        eventLoop_->SetEventListener(GetFd(), EventRead, eventCallbackPtr_.GetHandle());
    }
}

bool BalTcpServer::IsV6()
{
    return BalTcpSocket::IsV6Socket();
}

bool BalTcpServer::Close()
{
    if (eventLoop_)
    {
        eventLoop_->DeleteEventListener(GetFd(), EventRead);
    }
    return BalTcpSocket::Close();
}

uint32_t BalTcpServer::GetTimeout() const
{
    return maxTimeout_;
}

uint32_t BalTcpServer::GetMaxReadBufferSize() const
{
    return maxReadBufferSize_;
}

uint32_t BalTcpServer::GetMaxWriteBufferSize() const
{
    return maxWriteBufferSize_;
}

bool BalTcpServer::EraseTcpConnection(int id)
{
    mapConnPoolT::iterator iter = mapConnPool_.find(id);
    if (mapConnPool_.end() != iter)
    {
        mapConnPool_.erase(iter);
    }
    return true;
}

BalEventCallbackEnum BalTcpServer::ShoudAccept(int id, BalHandle<BalEventLoop> el)
{
    int accpetId = 0;
    if (!BalTcpSocket::Accpet(accpetId))
    {
        return EventRetComplete;
    }
    return EventRetContinue;
}
