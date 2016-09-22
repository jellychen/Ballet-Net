#include "BalHttpServer.h"
using namespace Ballet;
using namespace Network;
using namespace Protocol;

BalHttpServer::BalHttpServer(bool v6, BalHandle<BalEventLoop> eventLoop,
    uint32_t maxPackage, BalHandle<IBalHttpCallback> callback,
    uint32_t timeout, uint32_t maxReadBufferSize,
    uint32_t maxWriteBufferSize)
    :BalTcpSocket(v6), eventCallbackPtr_(this), eventHandle_(GetFd())
{
    eventLoop_ = eventLoop;
    maxTimeout_ = timeout;
    maxPackageSize_ = maxPackage;
    maxReadBufferSize_ = maxReadBufferSize;
    maxWriteBufferSize_ = maxWriteBufferSize;

    if (!callback || !callback->IsCallable())
    {
        throw std::runtime_error("BalTcpServer Construct Failed");
    }
    else
    {
        httpCallback_ = callback;
    }

    if (!eventLoop_ || !eventCallbackPtr_ || !SetNoBlock())
    {
        throw std::runtime_error("BalTcpServer Construct Failed");
    }
    else
    {
        eventCallbackPtr_->HookShouldRead(&BalHttpServer::ShoudAccept);
        eventLoop_->SetEventListener(eventHandle_, EventRead, eventCallbackPtr_);
    }
}

BalHttpServer::~BalHttpServer()
{
    if (eventLoop_)
    {
        eventLoop_->DeleteEventListener(eventHandle_, EventRead);
    }
}

bool BalHttpServer::IsV6()
{
    return BalTcpSocket::IsV6Socket();
}

bool BalHttpServer::Close()
{
    if (eventLoop_)
    {
        eventLoop_->DeleteEventListener(GetFd(), EventRead);
    }
    return BalTcpSocket::Close();
}

bool BalHttpServer::Start(BalHandle<BalInetAddress> addr)
{
    if (false == BindAddress(addr)) return false;
    if (false == Listen()) return false;
    return true;
}

uint32_t BalHttpServer::GetTimeout() const
{
    return maxTimeout_;
}

uint32_t BalHttpServer::GetMaxPackageSize() const
{
    return maxPackageSize_;
}

uint32_t BalHttpServer::GetMaxReadBufferSize() const
{
    return maxReadBufferSize_;
}

uint32_t BalHttpServer::GetMaxWriteBufferSize() const
{
    return maxWriteBufferSize_;
}

BalHandle<BalEventLoop> BalHttpServer::GetEventLoop() const
{
    return eventLoop_;
}

BalHandle<IBalHttpCallback> BalHttpServer::GetCallback() const
{
    return httpCallback_;
}

BalEventCallbackEnum BalHttpServer::ShoudAccept(int id, BalHandle<BalEventLoop> el)
{
    int accpetId = 0;
    if (!BalTcpSocket::Accpet(&accpetId))
    {
        return EventRetComplete;
    }

    try
    {
        BalHandle<BalHttpServer> server(this, shareUserCount_);
        BalHandle<BalHttpConnection> conn(new BalHttpConnection(accpetId, server));
        if (conn)
        {
            mapConnPool_[accpetId] = conn;
            conn->SetNoDelay(true); conn->SetReuseAddr(true);
            if (httpCallback_ && httpCallback_->IsCallable())
            {
                httpCallback_->OnConnect(conn, true);
            }
        }
    }
    catch (std::exception&)
    {
    }
    return EventRetNone;
}

bool BalHttpServer::EraseTcpConnection(int id)
{
    mapConnPoolT::iterator iter = mapConnPool_.find(id);
    if (mapConnPool_.end() != iter)
    {
        mapConnPool_.erase(iter);
    }
    return true;
}
