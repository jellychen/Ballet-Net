#include "BalTcpClient.h"
using namespace Ballet;
using namespace Ballet::Network;

BalTcpClient::BalTcpClient(bool v6,
    BalHandle<BalEventLoop> eventLoop,
    BalHandle<IBalProtocol> protocol, uint32_t maxPackage,
    BalHandle<IBalTcpCallback> callback,
    uint32_t maxReadBufferSize, uint32_t maxWriteBufferSize)
    :BalTcpSocket(v6),eventCallbackPtr_(this),eventHandle_(GetFd())
{
    if (!eventLoop || !protocol || !callback || !callback->IsCallable())
    {
        throw std::runtime_error("BalTcpClient Construct Failed!");
    }

    setDelayRelease_ = false;
    status_ = StatusNone;
    tcpProtocol_ = protocol;
    eventLoop_ = eventLoop;
    tcpCallback_ = callback;
    maxPackage_ = maxPackage;
    lastSendBufferTime_ = 0;
    maxReadBufferSize_ = maxReadBufferSize;
    maxWriteBufferSize_ = maxWriteBufferSize;

    if (!eventCallbackPtr_ || !SetNoBlock())
    {
        throw std::runtime_error("BalTcpClient Construct Failed");
    }
    else
    {
        eventCallbackPtr_->HookShouldRead(&BalTcpClient::ShouldRead);
        eventCallbackPtr_->HookShouldWrite(&BalTcpClient::ShouldWrite);
        eventLoop_->SetEventListener(eventHandle_, EventReadWrite, eventCallbackPtr_);
    }
}

bool BalTcpClient::IsV6()
{
    return BalTcpSocket::IsV6Socket();
}

bool BalTcpClient::Connect(BalHandle<BalInetAddress> addr, int timeout)
{
    return true;
}

bool BalTcpClient::Close(bool now)
{
    return true;
}

bool BalTcpClient::ShutdownWrite()
{
    return true;
}

bool BalTcpClient::WriteBuffer(const char* buffer, uint32_t len)
{
    return true;
}

bool BalTcpClient::WriteRawBuffer(const char* buffer, uint32_t len)
{
    return true;
}

bool BalTcpClient::Connect(BalHandle<BalInetAddress> addr) throw()
{
    return true;
}

bool BalTcpClient::BindAddress(BalHandle<BalInetAddress> addr) throw()
{
    return true;
}

uint32_t BalTcpClient::GetMaxPackageSize() const
{
    return maxPackage_;
}

uint32_t BalTcpClient::GetMaxReadBufferSize() const
{
    return maxPackage_;
}

uint32_t BalTcpClient::GetMaxWriteBufferSize() const
{
    return maxPackage_;
}

uint32_t BalTcpClient::GetLastSendBufferTime() const
{
    return maxPackage_;
}

BalHandle<BalEventLoop> BalTcpClient::GetEventLoop() const
{
    return eventLoop_;
}

BalHandle<IBalProtocol> BalTcpClient::GetProtocol() const
{
    return tcpProtocol_;
}

BalHandle<IBalTcpCallback> BalTcpClient::GetCallback() const
{
    return tcpCallback_;
}

BalEventCallbackEnum BalTcpClient::ShouldRead(int id, BalHandle<BalEventLoop> el)
{
    return EventRetNone;
}

BalEventCallbackEnum BalTcpClient::ShouldWrite(int id, BalHandle<BalEventLoop> el)
{
    return EventRetNone;
}
