#include "BalNetDefine.h"
#include "BalTcpServer.h"
#include "BalTcpConnection.h"
using namespace Ballet;
using namespace Network;

BalTcpConnection::BalTcpConnection(int id,
    BalHandle<BalTcpServer> server,
    BalHandle<BalEventLoop> eventLoop)
    :BalTcpSocket(id), eventCallbackPtr_(this)
{
    tcpServer_ = server;
    eventLoop_ = eventLoop; status_ = StatusEstablish;

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
    if (nullptr_() == buffer || 0 == len || !tcpServer_) return false;
    BalHandle<BalTcpConnection> conn(this, shareUserCount_);
    BalHandle<IBalTcpProtocol> protocol = tcpServer_->GetProtocol();
    if (!protocol) return false;
    return protocol->Encode(buffer, len, conn);
}

bool BalTcpConnection::WriteRawBuffer(const char* buffer, uint32_t len)
{
    if (nullptr_() == buffer || 0 == len) return false;
    return true;
}

uint32_t BalTcpConnection::TimeoutTime() const
{
    if (!tcpServer_) return 0;
    return tcpServer_->GetTimeout();
}

uint32_t BalTcpConnection::MaxReadBufferSize() const
{
    if (!tcpServer_) return 0;
    return tcpServer_->GetMaxReadBufferSize();
}

uint32_t BalTcpConnection::MaxWriteBufferSize() const
{
    if (!tcpServer_) return 0;
    return tcpServer_->GetMaxWriteBufferSize();
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
