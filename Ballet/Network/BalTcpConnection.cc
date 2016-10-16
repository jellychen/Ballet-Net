#include "BalNetDefine.h"
#include "BalTcpServer.h"
#include "BalTcpConnection.h"
using namespace Ballet;
using namespace Network;

BalTcpConnection::BalTcpConnection(int fd, BalHandle<BalTcpServer> server)
    :BalTcpSocket(fd), eventCallbackPtr_(this)
    ,timerCallbackPtr_(this), protocolWantSize_(-1) ,eventHandle_(fd)
{
    tcpServer_ = server;
    status_ = StatusEstablish;

    if (!eventCallbackPtr_ || !tcpServer_ || !SetNoBlock())
    {
        throw std::runtime_error("BalTcpConnection Construct Failed! @1");
        return;
    }
    else
    {
        timerCallbackPtr_->HookOnTime(&BalTcpConnection::OnTime);
        eventCallbackPtr_->HookShouldRead(&BalTcpConnection::ShouldRead);
        eventCallbackPtr_->HookShouldWrite(&BalTcpConnection::ShouldWrite);
    }

    lastReadTime_ = BootUtil::BalTimeStamp::GetCurrent();
    BalHandle<BalEventLoop> eventLoop = tcpServer_->GetEventLoop();

    if (!eventLoop)
    {
        throw std::runtime_error("BalTcpConnection Construct Failed! @2");
        return;
    }
    else
    {
        uint32_t timeout = (uint32_t)(tcpServer_->GetTimeout());
        if (timeout > 0)
        {
            eventLoop->SetTimerOut(0, timerCallbackPtr_, timeout);
        }
        eventLoop->SetEventListener(eventHandle_, EventReadWrite, eventCallbackPtr_);
    }
}

BalTcpConnection::~BalTcpConnection()
{

}

bool BalTcpConnection::IsV6()
{
    return BalTcpSocket::IsV6Socket();
}

bool BalTcpConnection::Close(bool now)
{
    if (StatusConnecting != status_ && StatusEstablish != status_)
    {
        return false;
    }

    if (false == now || 0 == writeBuffer_.GetSize())
    {
        DoCloseProcedure(true, true);
    }
    else
    {
        status_ = StatusClosing;
    }
    return true;
}

bool BalTcpConnection::ShutdownWrite()
{
    return BalTcpSocket::ShutdownWrite();
}

bool BalTcpConnection::WriteBuffer(const char* buffer, uint32_t len)
{
    if (StatusEstablish != status_) return false;
    if (nullptr_() == buffer || 0 == len || !tcpServer_) return false;

    BalHandle<BalTcpConnection> conn(this, shareUserCount_);
    BalHandle<BalChannel> channel =
        dynamic_cast_<BalTcpConnection, BalChannel>(conn);
    BalHandle<IBalProtocol> protocol = tcpServer_->GetProtocol();
    if (!protocol) return false;
    return protocol->Encode(buffer, len, channel);
}

bool BalTcpConnection::WriteRawBuffer(const char* buffer, uint32_t len)
{
    if (StatusEstablish != status_) return false;
    if (nullptr_() == buffer || 0 == len || !tcpServer_) return false;

    if (writeBuffer_.GetSize() <= 0)
    {
        bool closed = false;
        uint32_t writeSize = BalTcpSocket::WriteBuffer(buffer, len, &closed);

        if (closed)
        {
            DoCloseProcedure(false, true);
            return false;
        }
        else
        {
            writeBuffer_.AppendBuffer(buffer + writeSize, (size_t)(len - writeSize));
        }
    }
    else
    {
        writeBuffer_.AppendBuffer(buffer, (size_t)(len));
    }

    if (tcpServer_->GetMaxWriteBufferSize() <= writeBuffer_.GetSize())
    {
        BalHandle<BalTcpConnection> conn(this, shareUserCount_);
        BalHandle<IBalTcpCallback> callback = tcpServer_->GetCallback();
        if (callback && callback->IsCallable())
        {
            callback->OnWriteBufferFull(conn);
        }
    }
    else if (0 == writeBuffer_.GetSize())
    {
        BalHandle<BalTcpConnection> conn(this, shareUserCount_);
        BalHandle<IBalTcpCallback> callback = tcpServer_->GetCallback();
        if (callback && callback->IsCallable())
        {
            callback->OnWriteBufferDrain(conn);
        }
    }
    return true;
}

bool BalTcpConnection::BroadcastRawBuffer(const char* buffer, uint32_t len)
{
    if (!buffer || 0 == len || !tcpServer_) return false;
    return tcpServer_->BroadcastRawBuffer(buffer, len);
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

BalHandle<BalInetAddress> BalTcpConnection::GetPeer() const
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

bool BalTcpConnection::DoCloseProcedure(bool accord, bool delEvent)
{
    BalHandle<BalTcpConnection> conn(this, shareUserCount_);

    if (tcpServer_)
    {
        BalHandle<BalEventLoop> eventLoop = tcpServer_->GetEventLoop();
        if (eventLoop)
        {
            if (true == delEvent)
            {
                eventLoop->DeleteEventListener(eventHandle_, EventReadWrite);
            }
            eventLoop->RemoveTimer(0, timerCallbackPtr_.GetHandle());
        }

        BalHandle<BalElement> element
            = dynamic_cast_<BalTcpConnection, BalElement>(conn);
        if (element && eventLoop)
        {
            eventLoop->AddDelayReleaseElement(element);
        }
        tcpServer_->EraseTcpConnection(GetFd());
    }

    BalTcpSocket::Close(); status_ = StatusClosed;
    BalHandle<IBalTcpCallback> callback = tcpServer_->GetCallback();
    if (callback && callback->IsCallable())
    {
        callback->OnClose(conn, accord);
    }
    return true;
}

bool BalTcpConnection::OnReceiveBuffer(const char* buffer, uint32_t len)
{
    BalHandle<BalTcpConnection> conn(this, shareUserCount_);
    BalHandle<IBalTcpCallback> callback = tcpServer_->GetCallback();
    if (callback && callback->IsCallable())
    {
        callback->OnReceive(conn, buffer, len);
    }
    return true;
}

void BalTcpConnection::OnTime(uint32_t id, BalHandle<BalTimer> timer)
{
    int64_t current = BootUtil::BalTimeStamp::GetCurrent();
    int64_t timeout = (int64_t)tcpServer_->GetTimeout();
    if (current - lastReadTime_ >= timeout)
    {
        DoCloseProcedure(true, true);
    }
    else
    {
        uint32_t outTime = (uint32_t)(timeout - current + lastReadTime_);
        BalHandle<BalEventLoop> eventLoop = tcpServer_->GetEventLoop();
        if (eventLoop)
        {
            eventLoop->SetTimerOut(0, timerCallbackPtr_.GetHandle(), outTime);
        }
    }
}

BalEventCallbackEnum BalTcpConnection::ShouldRead(int id, BalHandle<BalEventLoop> el)
{
    if (StatusEstablish != status_ || !tcpServer_)
    {
         return EventRetClose;
    }

    bool closed = false;
    char buffer[MAX_READFD_SIZE] = {0};
    BalEventCallbackEnum ret = EventRetContinue;
    uint32_t readSize = ReadBuffer(buffer, MAX_READFD_SIZE, &closed);

    if (closed)
    {
        DoCloseProcedure(false, true);
        return EventRetClose;
    }
    lastReadTime_ = BootUtil::BalTimeStamp::GetCurrent();

    if (0 < readSize)
    {
        readBuffer_.AppendBuffer(buffer, readSize);
    }

    if (readSize < MAX_READFD_SIZE || 0 == readSize)
    {
        ret = EventRetComplete;
    }

    while (readBuffer_.GetSize() > 0)
    {
        char* rawBuffer = readBuffer_.RawBuffer();
        size_t rawBufferSize = readBuffer_.GetSize();

        if (-1 == protocolWantSize_)
        {
            uint32_t wantSize = -1;
            BalProtocolStatus ret = tcpServer_->GetProtocol()
                ->CalSize(rawBuffer, (uint32_t)rawBufferSize, &wantSize);

            if (StatusFail == ret)
            {
                DoCloseProcedure(true, true);
                return EventRetClose;
            }
            else if (StatusSuccess == ret)
            {
                protocolWantSize_ = wantSize;
            }
        }

        if (-1 != protocolWantSize_)
        {
            if ((uint32_t)rawBufferSize >= protocolWantSize_)
            {
                BalHandle<BalTcpConnection> conn(this, shareUserCount_);
                BalHandle<BalChannel> channel =
                    dynamic_cast_<BalTcpConnection, BalChannel>(conn);
                bool ret = tcpServer_->GetProtocol()
                    ->Decode(rawBuffer, (uint32_t)protocolWantSize_, channel);

                if (false == ret)
                {
                    DoCloseProcedure(true, true);
                    return EventRetClose;
                }
                else
                {
                    readBuffer_.ConsumeBuffer((size_t)protocolWantSize_);
                    protocolWantSize_ = -1;
                }
            }
            else if (protocolWantSize_ > tcpServer_->GetMaxPackageSize())
            {
                DoCloseProcedure(true, true);
                return EventRetClose;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    return ret;
}

BalEventCallbackEnum BalTcpConnection::ShouldWrite(int id, BalHandle<BalEventLoop> el)
{
    if (0 == writeBuffer_.GetSize()) return EventRetAgain;
    char* buffer = (char*)writeBuffer_.RawBuffer();
    uint32_t size = (uint32_t)writeBuffer_.GetSize();
    uint32_t writeSize = WriteBuffer(buffer, size);

    if (0 == writeSize || (-1 == writeSize && EAGAIN != errno))
    {
        DoCloseProcedure(false, true);
        return EventRetClose;
    }
    writeBuffer_.ConsumeBuffer((size_t)writeSize);

    if (size > writeSize)
    {
        return EventRetComplete;
    }
    else if (size == writeSize)
    {
        if (StatusClosing == status_)
        {
            DoCloseProcedure(true, true);
            return EventRetClose;
        }
        else
        {
            BalHandle<BalTcpConnection> conn(this, shareUserCount_);
            BalHandle<IBalTcpCallback> callback = tcpServer_->GetCallback();
            if (callback && callback->IsCallable())
            {
                callback->OnWriteBufferDrain(conn);
            }
        }
        return EventRetComplete;
    }
    return EventRetNone;
}
