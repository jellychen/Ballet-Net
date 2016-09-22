#include "BalHttpServer.h"
#include "BalHttpConnection.h"
using namespace Ballet;
using namespace Network;
using namespace Protocol;

BalHttpConnection::BalHttpConnection(int id, BalHandle<BalHttpServer> server)
    :BalTcpSocket(id), eventCallbackPtr_(this)
    ,timerCallbackPtr_(this), eventHandle_(GetFd())
{
    httpServer_ = server;
    status_ = StatusEstablish;

    if (!eventCallbackPtr_ || !httpServer_)
    {
        throw std::runtime_error("BalHttpConnection Construct Failed! @1");
        return;
    }
    else
    {
        timerCallbackPtr_->HookOnTime(&BalHttpConnection::OnTime);
        eventCallbackPtr_->HookShouldRead(&BalHttpConnection::ShouldRead);
        eventCallbackPtr_->HookShouldWrite(&BalHttpConnection::ShouldWrite);
    }

    lastReadTime_ = BootUtil::BalTimeStamp::GetCurrent();
    BalHandle<BalEventLoop> eventLoop = httpServer_->GetEventLoop();

    if (!eventLoop)
    {
        throw std::runtime_error("BalHttpConnection Construct Failed! @2");
        return;
    }
    else
    {
        uint32_t timeout = (uint32_t)(httpServer_->GetTimeout());
        if (timeout > 0)
        {
            eventLoop->SetTimerOut(0, timerCallbackPtr_, timeout);
        }
        eventLoop->SetEventListener(eventHandle_, EventReadWrite, eventCallbackPtr_);
    }
}

BalHttpConnection::~BalHttpConnection()
{

}

bool BalHttpConnection::IsV6()
{
    return BalTcpSocket::IsV6Socket();
}

bool BalHttpConnection::Close(bool now)
{
    if (StatusConnecting != status_ || StatusEstablish != status_)
    {
        return false;
    }

    if (true == now || 0 == writeBuffer_.GetSize())
    {
        DoCloseProcedure(true, true);
    }
    else
    {
        status_ = StatusClosing;
    }
    return true;
}

bool BalHttpConnection::ShutdownWrite()
{
    return BalTcpSocket::ShutdownWrite();
}

bool BalHttpConnection::WriteBuffer(const char* buffer, uint32_t len)
{
    return true;
}

bool BalHttpConnection::WriteRawBuffer(const char* buffer, uint32_t len)
{
    return true;
}

uint32_t BalHttpConnection::TimeoutTime() const
{
    if (!httpServer_) return 0;
    return httpServer_->GetTimeout();
}

uint32_t BalHttpConnection::MaxReadBufferSize() const
{
    if (!httpServer_) return 0;
    return httpServer_->GetMaxReadBufferSize();
}

uint32_t BalHttpConnection::MaxWriteBufferSize() const
{
    if (!httpServer_) return 0;
    return httpServer_->GetMaxWriteBufferSize();
}

BalConnStatusEnum BalHttpConnection::GetStatus() const
{
    return status_;
}

BalHandle<BalInetAddress> BalHttpConnection::GetPeer() const
{
    struct sockaddr_in6 addr;
    memset((void*)&addr, 0, sizeof(struct sockaddr_in6));
    socklen_t len = (socklen_t)sizeof(struct sockaddr_in6);
    ::getsockname(GetFd(), (struct sockaddr*)&addr, &len);
    if (AF_INET6 == (*(struct sockaddr*)&addr).sa_family)
    {
        sockaddr_in6& addr6 = (*(struct sockaddr_in6*)&addr);
        return BalHandle<BalInetAddress>(new BalInetAddress(addr6));
    }
    else
    {
        sockaddr_in& addr4 = (*(struct sockaddr_in*)&addr);
        return BalHandle<BalInetAddress>(new BalInetAddress(addr4));
    }
}

BalHandle<BalInetAddress> BalHttpConnection::GetLocal() const
{
    struct sockaddr_in6 addr;
    memset((void*)&addr, 0, sizeof(struct sockaddr_in6));
    socklen_t len = (socklen_t)sizeof(struct sockaddr_in6);
    ::getpeername(GetFd(), (struct sockaddr*)&addr, &len);
    if (AF_INET6 == (*(struct sockaddr*)&addr).sa_family)
    {
        sockaddr_in6& addr6 = (*(struct sockaddr_in6*)&addr);
        return BalHandle<BalInetAddress>(new BalInetAddress(addr6));
    }
    else
    {
        sockaddr_in& addr4 = (*(struct sockaddr_in*)&addr);
        return BalHandle<BalInetAddress>(new BalInetAddress(addr4));
    }
}

bool BalHttpConnection::DoCloseProcedure(bool accord, bool delEvent)
{
    return true;
}

bool BalHttpConnection::OnReceiveBuffer(const char* buffer, uint32_t len)
{
    return true;
}

void BalHttpConnection::OnTime(uint32_t id, BalHandle<BalTimer> timer)
{
}

BalEventCallbackEnum BalHttpConnection::ShouldRead(int id, BalHandle<BalEventLoop> el)
{
    return EventRetNone;
}

BalEventCallbackEnum BalHttpConnection::ShouldWrite(int id, BalHandle<BalEventLoop> el)
{
    return EventRetNone;
}
