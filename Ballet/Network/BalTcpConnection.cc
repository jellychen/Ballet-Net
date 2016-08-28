#include "BalNetDefine.h"
#include "BalTcpConnection.h"
using namespace Ballet;
using namespace Network;

BalTcpConnection::BalTcpConnection(int id,
    BalHandle<BalTcpServer> server,
    BalHandle<BalEventLoop> eventLoop,
    uint32_t maxReadBufferSize, uint32_t maxWriteBufferSize)
    :BalTcpSocket(id), eventCallbackPtr_(this)
{
    maxReadBufferSize_ = maxReadBufferSize;
    maxWriteBufferSize_ = maxWriteBufferSize;
    status_ = StatusNone; eventLoop_ = eventLoop;
    if (!eventLoop_ || !eventCallbackPtr_)
    {
        throw std::runtime_error("BalTcpConnection Construct Failed!");
    }
    else
    {
        eventCallbackPtr_->HookShouldRead(&BalTcpConnection::ShouldRead);
        eventCallbackPtr_->HookShouldWrite(&BalTcpConnection::ShouldWrite);
        eventLoop_->SetEventListener(GetFd(), EventReadWrite, eventCallbackPtr_);
    }
}

bool BalTcpConnection::IsV6()
{
    return BalTcpSocket::IsV6Socket();
}

bool BalTcpConnection::Close(bool now)
{
    if (StatusConnecting != status_ || StatusEstablish != status_)
    {
        return false;
    }

    return true;
}

bool BalTcpConnection::ShutdownWrite()
{
    return BalTcpSocket::ShutdownWrite();
}

bool BalTcpConnection::WriteBuffer(const char* buffer, uint32_t len)
{
    if (nullptr_() == buffer || 0 == len) return false;
    return true;
}

bool BalTcpConnection::WriteRawBuffer(const char* buffer, uint32_t len)
{
    if (nullptr_() == buffer || 0 == len) return false;
    return true;
}

uint32_t BalTcpConnection::MaxReadBufferSize() const
{
    return maxReadBufferSize_;
}

uint32_t BalTcpConnection::MaxWriteBufferSize() const
{
    return maxWriteBufferSize_;
}

BalConnStatusEnum BalTcpConnection::GetStatus() const
{
    return status_;
}

BalHandle<BalInetAddress> BalTcpConnection::GetLocal() const
{
    return BalHandle<BalInetAddress>(new BalInetAddress(10, true, true));
}

BalHandle<BalInetAddress> BalTcpConnection::GetPeer() const
{
    return BalHandle<BalInetAddress>(new BalInetAddress(10, true, true));
}

BalEventCallbackEnum BalTcpConnection::ShouldRead(int id, BalHandle<BalEventLoop> el)
{
    return EventRetNone;
}

BalEventCallbackEnum BalTcpConnection::ShouldWrite(int id, BalHandle<BalEventLoop> el)
{
    return EventRetNone;
}
