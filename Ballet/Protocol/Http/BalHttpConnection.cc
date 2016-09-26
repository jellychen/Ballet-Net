#include "BalHttpServer.h"
#include "BalHttpConnection.h"
#include "BalHttpParserCallback.h"
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

    http_parser_init(&requestParser_, HTTP_REQUEST);
    requestParser_.data = (void*)(this);
    memset(&requestSetting_, 0, sizeof(requestSetting_));
    requestSetting_.on_message_begin = __gOnHttpBegin;
    requestSetting_.on_url = __gOnUrlCallback;
    requestSetting_.on_header_field = __gOnHeaderField;
    requestSetting_.on_header_value = __gOnHeaderValue;
    requestSetting_.on_headers_complete = __gOnHeaderComplete;
    requestSetting_.on_body = __gOnContentBody;
    requestSetting_.on_status = __gOnStatus;
    requestSetting_.on_message_complete = __gOnHttpComplete;
    requestSetting_.on_chunk_header = __gOnChunkHeader;
    requestSetting_.on_chunk_complete = __gOnChunkComplete;

    requestBodySize_ = 0;
    requestKeepAlive_ = false;
    respondKeepAlive_ = false;
    respondChunked_ = false;
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

uint32_t BalHttpConnection::TimeoutTime() const
{
    if (!httpServer_) return 0;
    return httpServer_->GetTimeout();
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

BalHttpMethod BalHttpConnection::GetHttpMethod() const
{
    return HttpUnknown;
}

void BalHttpConnection::GetHttpUrl(std::string*) const
{

}

void BalHttpConnection::GetHttpVersion(int*, int*) const
{

}

void BalHttpConnection::GetHttpHeaderField(const char*, std::string*) const
{

}

bool BalHttpConnection::GetKeepAlive() const
{
    return requestKeepAlive_;
}

void BalHttpConnection::RespondBegin()
{
    respondHttpHeadBuffer_ = "HTTP/";
}

void BalHttpConnection::RespondVersion(int major, int minor)
{
    char versionStr[128] = {0};
    sprintf(versionStr, "%d.%d ", major, minor);
    respondHttpHeadBuffer_ += versionStr;
}

void BalHttpConnection::RespondKeepAlive()
{
    respondKeepAlive_ = true;
    respondHttpHeadBuffer_ += "Connection: keep-alive\r\n";
}

void BalHttpConnection::RespondChunked()
{
    respondChunked_ = true;
    respondHttpHeadBuffer_ += "Transfer-Encoding: chunked\r\n";
}

void BalHttpConnection::RespondStatus(int status, const char* info)
{
    char statusStr[20] = {0};
    sprintf(statusStr, "%d ", status);
    respondHttpHeadBuffer_ += statusStr;
    respondHttpHeadBuffer_ += "\r\n";
}

void BalHttpConnection::RespondContentType(const char* type)
{
    if (type)
    {
        respondHttpHeadBuffer_ += "Content-type: ";
        respondHttpHeadBuffer_ += type;
        respondHttpHeadBuffer_ += "\r\n";
    }
}

void BalHttpConnection::RespondContentLength(int length)
{
    char lengthStr[20] = {0};
    sprintf(lengthStr, "%d\r\n", length);
    respondHttpHeadBuffer_ += "Content-Length: ";
    respondHttpHeadBuffer_ += lengthStr;
}

void BalHttpConnection::RespondHeader(const char* field, const char* value)
{
    if (field && value)
    {
        respondHttpHeadBuffer_ += field;
        respondHttpHeadBuffer_ += ": ";
        respondHttpHeadBuffer_ += value;
        respondHttpHeadBuffer_ += "\r\n";
    }
}

void BalHttpConnection::RespondHeaderComplete()
{
    respondHttpHeadBuffer_ += "\r\n";
}

void BalHttpConnection::RespondBody(const char* content, int size)
{

}

void BalHttpConnection::RespondChunk(const char* content, int size)
{

}

void BalHttpConnection::RespondChunkComplete()
{

}

void BalHttpConnection::RespondComplete()
{

}

bool BalHttpConnection::WriteRawBuffer(const char* buffer, uint32_t size)
{
    return true;
}

bool BalHttpConnection::DoCloseProcedure(bool accord, bool delEvent)
{
    return true;
}

void BalHttpConnection::OnTime(uint32_t id, BalHandle<BalTimer> timer)
{
}

uint32_t BalHttpConnection::DoHttpParser(const char* buffer, uint32_t len)
{
    return (uint32_t)http_parser_execute(&requestParser_, &requestSetting_, buffer, len);
}

BalEventCallbackEnum BalHttpConnection::ShouldRead(int id, BalHandle<BalEventLoop> el)
{
    if (StatusEstablish != status_ || !httpServer_)
    {
         return EventRetClose;
    }

    BalHandle<BalHttpConnection> conn(this, shareUserCount_);
    BalHandle<IBalHttpCallback> callback = httpServer_->GetCallback();
    bool callbackAble = callback && callback->IsCallable();

    char buffer[MAX_READFD_SIZE] = {0};
    BalEventCallbackEnum ret = EventRetContinue;
    uint32_t readSize = ReadBuffer(buffer, MAX_READFD_SIZE);
    if (0 == readSize || (-1 == readSize && EAGAIN != errno))
    {
        DoHttpParser(nullptr_(), 0);
        DoCloseProcedure(false, true);
        return EventRetClose;
    }
    lastReadTime_ = BootUtil::BalTimeStamp::GetCurrent();

    if (readSize > 0)
    {
        if (readSize != DoHttpParser(buffer, readSize))
        {
            if (callbackAble)
            {
                callback->OnHttpError(conn, HttpErrorParser);
            }
            DoCloseProcedure(true, true);
            return EventRetClose;
        }

        uint32_t maxPackageSize = httpServer_->GetMaxPackageSize();
        if (maxPackageSize < requestBodySize_)
        {
            if (callbackAble)
            {
                callback->OnHttpError(conn, HttpErrorExceed);
            }
            DoCloseProcedure(true, true);
            return EventRetClose;
        }
    }

    if (readSize < MAX_READFD_SIZE)
    {
        return EventRetComplete;
    }
    else
    {
        return EventRetContinue;
    }
}

BalEventCallbackEnum BalHttpConnection::ShouldWrite(int id, BalHandle<BalEventLoop> el)
{
    if (StatusEstablish != status_) return EventRetAgain;
    if (0 == writeBuffer_.GetSize()) return EventRetAgain;
    char* buffer = (char*)writeBuffer_.RawBuffer();
    uint32_t size = (uint32_t)writeBuffer_.GetSize();
    uint32_t writeSize = WriteBuffer(buffer, size);

    if (0 == writeSize)
    {
        DoCloseProcedure(false, true);
        return EventRetClose;
    }
    else if (size > writeSize)
    {
        writeBuffer_.ConsumeBuffer((size_t)writeSize);
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
            BalHandle<BalHttpConnection> conn(this, shareUserCount_);
            BalHandle<IBalHttpCallback> callback = httpServer_->GetCallback();
            if (callback && callback->IsCallable())
            {
                callback->OnWriteBufferDrain(conn);
            }
            return EventRetComplete;
        }
    }
    return EventRetNone;
}

int BalHttpConnection::_OnHttpBegin(http_parser* parser)
{
    if (httpServer_)
    {
        BalHandle<IBalHttpCallback> callback = httpServer_->GetCallback();
        if (callback && callback->IsCallable())
        {
            BalHandle<BalHttpConnection> conn(this, shareUserCount_);
            callback->OnHttpBegin(conn);
        }
    }
    return 0;
}

int BalHttpConnection::_OnUrlCallback(http_parser* parser, const char* buffer, size_t len)
{
    if (buffer && len > 0)
    {
        requestUrl_.append(buffer, len);
    }
    return 0;
}

int BalHttpConnection::_OnHeaderField(http_parser* parser, const char* buffer, size_t len)
{
    if (requestHeaderFieldKey_.length() > 0 && requestHeaderFieldValue_.length())
    {
        requestHeaderField_[requestHeaderFieldKey_] = requestHeaderFieldValue_;
        requestHeaderFieldKey_.clear();
        requestHeaderFieldValue_.clear();
    }

    if (buffer && len > 0)
    {
        requestHeaderFieldKey_.append(buffer, len);
    }
    return 0;
}

int BalHttpConnection::_OnHeaderValue(http_parser* parser, const char* buffer, size_t len)
{
    if (buffer && len > 0)
    {
        requestHeaderFieldValue_.append(buffer, len);
    }
    return 0;
}

int BalHttpConnection::_OnHeaderComplete(http_parser* parser)
{
    if (httpServer_)
    {
        BalHandle<IBalHttpCallback> callback = httpServer_->GetCallback();
        if (callback && callback->IsCallable())
        {
            BalHandle<BalHttpConnection> conn(this, shareUserCount_);
            callback->OnHttpHeaderComplete(conn);
        }
    }

    if (parser)
    {
        requestKeepAlive_ = http_should_keep_alive(parser);
    }
    return 0;
}

int BalHttpConnection::_OnStatus(http_parser* parser, const char* buffer, size_t len)
{
    return 0;
}

int BalHttpConnection::_OnContentBody(http_parser* parser, const char* buffer, size_t len)
{
    if (httpServer_)
    {
        BalHandle<IBalHttpCallback> callback = httpServer_->GetCallback();
        if (callback && callback->IsCallable())
        {
            BalHandle<BalHttpConnection> conn(this, shareUserCount_);
            callback->OnHttpBody(conn, buffer, len);
        }
    }
    requestBodySize_ += len;
    return 0;
}

int BalHttpConnection::_OnHttpComplete(http_parser* parser)
{
    if (httpServer_)
    {
        BalHandle<IBalHttpCallback> callback = httpServer_->GetCallback();
        if (callback && callback->IsCallable())
        {
            BalHandle<BalHttpConnection> conn(this, shareUserCount_);
            callback->OnHttpComplete(conn);
        }
    }
    return 0;
}

int BalHttpConnection::_OnChunkHeader(http_parser* parser)
{
    return 0;
}

int BalHttpConnection::_OnChunkComplete(http_parser* parser)
{
    return 0;
}
