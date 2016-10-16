#include "BalTcpClient.h"
using namespace Ballet;
using namespace Ballet::Network;
#define BALTCP_CONNECT_TIMEOUT          0
#define BALTCP_INTERACTIVE_TIMEOUT      1

BalTcpClient::BalTcpClient(bool v6,
    BalHandle<BalEventLoop> eventLoop,
    BalHandle<IBalProtocol> protocol, uint32_t maxPackage,
    BalHandle<IBalTcpClientCallback> callback, uint32_t timeout,
    uint32_t maxReadBufferSize, uint32_t maxWriteBufferSize)
    :BalTcpSocket(v6), eventCallbackPtr_(this)
    ,eventHandle_(GetFd()), timerCallbackPtr_(this), protocolWantSize_(-1)
{
    if (!eventLoop || !protocol || !callback || !callback->IsCallable())
    {
        throw std::runtime_error("BalTcpClient Construct Failed!@1");
    }

    status_ = StatusNone;
    tcpProtocol_ = protocol;
    eventLoop_ = eventLoop;
    tcpCallback_ = callback;
    maxPackage_ = maxPackage;
    maxTimeout_ = timeout;
    setMaintainUtilBufferDrain_ = false;
    maxReadBufferSize_ = maxReadBufferSize;
    maxWriteBufferSize_ = maxWriteBufferSize;
    lastReadTime_ = BootUtil::BalTimeStamp::GetCurrent();

    if (!eventCallbackPtr_ || !timerCallbackPtr_ || !SetNoBlock())
    {
        throw std::runtime_error("BalTcpClient Construct Failed!@2");
    }
    else
    {
        timerCallbackPtr_->HookOnTime(&BalTcpClient::OnTime);
        eventCallbackPtr_->HookShouldRead(&BalTcpClient::ShouldRead);
        eventCallbackPtr_->HookShouldWrite(&BalTcpClient::ShouldWrite);
        eventLoop_->SetEventListener(eventHandle_, EventReadWrite, eventCallbackPtr_);
    }
}

bool BalTcpClient::IsV6()
{
    return BalTcpSocket::IsV6Socket();
}

bool BalTcpClient::Close(bool now)
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

bool BalTcpClient::CloseMaintainUtilBufferDrain()
{
    if (StatusConnecting != status_ && StatusEstablish != status_)
    {
        return false;
    }

    if (setMaintainUtilBufferDrain_)
    {
        return true;
    }

    status_ = StatusClosing;
    setMaintainUtilBufferDrain_ = true;
    BalHandle<BalTcpClient> client(this, shareUserCount_);
    BalHandle<BalElement> element =
        dynamic_cast_<BalTcpClient, BalElement>(client);
    eventLoop_->AddHoldSomeElement((long)((void*)(this)), element);
}

bool BalTcpClient::ShutdownWrite()
{
    return BalTcpSocket::ShutdownWrite();
}

bool BalTcpClient::WriteBuffer(const char* buffer, uint32_t len)
{
    if (StatusEstablish != status_) return false;
    if (nullptr_() == buffer || 0 == len) return false;
    BalHandle<BalTcpClient> client(this, shareUserCount_);
    BalHandle<BalChannel> channel =
        dynamic_cast_<BalTcpClient, BalChannel>(client);
    return tcpProtocol_->Encode(buffer, len, channel);
}

bool BalTcpClient::WriteRawBuffer(const char* buffer, uint32_t len)
{
    if (StatusEstablish != status_) return false;
    if (nullptr_() == buffer || 0 == len) return false;
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

    if (maxWriteBufferSize_ <= writeBuffer_.GetSize())
    {
        BalHandle<BalTcpClient> client(this, shareUserCount_);
        if (tcpCallback_ && tcpCallback_->IsCallable())
        {
            tcpCallback_->OnWriteBufferFull(client);
        }
    }
    else if (0 == writeBuffer_.GetSize())
    {
        BalHandle<BalTcpClient> client(this, shareUserCount_);
        if (tcpCallback_ && tcpCallback_->IsCallable())
        {
            tcpCallback_->OnWriteBufferDrain(client);
        }
    }
    return true;
}

bool BalTcpClient::BroadcastRawBuffer(const char* buffer, uint32_t len)
{
    return WriteBuffer(buffer, len);
}

bool BalTcpClient::Connect(BalHandle<BalInetAddress> addr, int timeout)
{
    if (StatusNone != status_) return false;
    bool connecting = false;
    bool ret = BalTcpSocket::Connect(addr, &connecting);
    do
    {
        if (true == ret)
        {
            status_ = StatusEstablish;
            BalHandle<BalTcpClient> client(this, shareUserCount_);
            if (tcpCallback_ && tcpCallback_->IsCallable())
            {
                tcpCallback_->OnConnect(client, true);
            }
            eventLoop_->SetTimerOut(BALTCP_INTERACTIVE_TIMEOUT, timerCallbackPtr_, timeout);
            break;
        }
        else if (true == connecting && timeout >= 0)
        {
            status_ = StatusConnecting;
            eventLoop_->SetTimerOut(BALTCP_CONNECT_TIMEOUT, timerCallbackPtr_, timeout);
            break;
        }
        return false;
    } while (0);
    return true;
}

bool BalTcpClient::BindAddress(BalHandle<BalInetAddress> addr) throw()
{
    return BalTcpSocket::BindAddress(addr);
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

BalHandle<IBalTcpClientCallback> BalTcpClient::GetCallback() const
{
    return tcpCallback_;
}

bool BalTcpClient::DoCloseProcedure(bool accord, bool delEvent)
{
    BalHandle<BalTcpClient> client(this, shareUserCount_);
    if (true == delEvent)
    {
        eventLoop_->DeleteEventListener(eventHandle_, EventReadWrite);
    }
    eventLoop_->RemoveTimer(BALTCP_INTERACTIVE_TIMEOUT, timerCallbackPtr_);

    BalTcpSocket::Close(); status_ = StatusClosed;
    if (tcpCallback_ && tcpCallback_->IsCallable())
    {
        tcpCallback_->OnClose(client, accord);
    }

    // note: close do clear
    if (setMaintainUtilBufferDrain_)
    {
        eventLoop_->RemoveHoldElement((long)((void*)(this)));
        BalHandle<BalElement> element
            = dynamic_cast_<BalTcpClient, BalElement>(client);
        eventLoop_->AddDelayReleaseElement(element);
    }
    return true;
}

bool BalTcpClient::OnReceiveBuffer(const char* buffer, uint32_t len)
{
    BalHandle<BalTcpClient> client(this, shareUserCount_);
    if (tcpCallback_ && tcpCallback_->IsCallable())
    {
        tcpCallback_->OnReceive(client, buffer, len);
    }
    return true;
}

void BalTcpClient::OnTime(uint32_t id, BalHandle<BalTimer> timer)
{
    if (BALTCP_CONNECT_TIMEOUT == id)
    {
        status_ = StatusNone;
        BalHandle<BalTcpClient> conn(this, shareUserCount_);
        if (tcpCallback_ && tcpCallback_->IsCallable())
        {
            tcpCallback_->OnConnect(conn, false);
        }
    }
    else if (BALTCP_INTERACTIVE_TIMEOUT == id)
    {
        int64_t current = BootUtil::BalTimeStamp::GetCurrent();
        if (current - lastReadTime_ >= maxTimeout_)
        {
            DoCloseProcedure(true, true);
        }
        else
        {
            uint32_t outTime = (uint32_t)(maxTimeout_ - current + lastReadTime_);
            eventLoop_->SetTimerOut(BALTCP_INTERACTIVE_TIMEOUT, timerCallbackPtr_, outTime);
        }
    }
}

BalEventCallbackEnum BalTcpClient::ShouldRead(int id, BalHandle<BalEventLoop> el)
{
    if (StatusEstablish != status_)
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
            BalProtocolStatus ret = tcpProtocol_->
                CalSize(rawBuffer, (uint32_t)rawBufferSize, &wantSize);

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
                BalHandle<BalTcpClient> client(this, shareUserCount_);
                BalHandle<BalChannel> channel =
                    dynamic_cast_<BalTcpClient, BalChannel>(client);
                bool ret = tcpProtocol_->
                    Decode(rawBuffer, (uint32_t)protocolWantSize_, channel);

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
            else if (protocolWantSize_ > maxPackage_)
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

BalEventCallbackEnum BalTcpClient::ShouldWrite(int id, BalHandle<BalEventLoop> el)
{
    if (StatusConnecting == status_)
    {
        int error = 0; socklen_t len = sizeof(error);
        if (0 == ::getsockopt(id, SOL_SOCKET, SO_ERROR, &error, &len) && 0 == error)
        {
            status_ = StatusEstablish;
        }
        else
        {
            status_ = StatusNone;
        }

        BalHandle<BalTcpClient> conn(this, shareUserCount_);
        if (tcpCallback_ && tcpCallback_->IsCallable())
        {
            tcpCallback_->OnConnect(conn, StatusEstablish == status_);
        }
        eventLoop_->RemoveTimer(BALTCP_CONNECT_TIMEOUT, timerCallbackPtr_);
    }

    if (0 == writeBuffer_.GetSize()) return EventRetAgain;

    bool closed = false;
    char* buffer = (char*)writeBuffer_.RawBuffer();
    uint32_t size = (uint32_t)writeBuffer_.GetSize();
    uint32_t writeSize = BalTcpSocket::WriteBuffer(buffer, size, &closed);

    if (closed)
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
            BalHandle<BalTcpClient> client(this, shareUserCount_);
            if (tcpCallback_ && tcpCallback_->IsCallable())
            {
                tcpCallback_->OnWriteBufferDrain(client);
            }
        }
        return EventRetComplete;
    }
}
