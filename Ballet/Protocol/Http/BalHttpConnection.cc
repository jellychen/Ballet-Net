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
    httpServer_ = server; status_ = StatusEstablish;

    if (!eventCallbackPtr_ || !timerCallbackPtr_ || !httpServer_ || !SetNoBlock())
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
    currentChunkedSize_ = 0;
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
    switch (request_parser_.method)
    {
        case 0:
            return HttpDelete;
        case 1:
            return HttpGet;
        case 2:
            return HttpHead;
        case 3:
            return HttpPost;
        case 4:
            return HttpPut;
        default:
            return HttpUnknown;
    }
    return HttpUnknown;
}

void BalHttpConnection::GetHttpUrl(std::string* url) const
{
    if (url)
    {
        *url = requestUrl_;
    }
}

void BalHttpConnection::GetHttpVersion(int* major, int* minor) const
{
    if (!major)
    {
        *major = request_parser_.http_major;
    }

    if (!minor)
    {
        *minor = request_parser_.http_minor;
    }
}

void BalHttpConnection::GetHttpHeaderField(const char* key, std::string* value) const
{
    if (!value) return;
    *value = ""; if (!key) return;

    std::string fieldKey(key);
    mapPoolT::const_iterator iter = requestHeaderField_.find(fieldKey);
    if (requestHeaderField_.end() != iter)
    {
        *value = iter->second;
    }
}

bool BalHttpConnection::GetKeepAlive() const
{
    return requestKeepAlive_;
}

bool BalHttpConnection::ParserGetParams() const
{
    return true;
}

bool BalHttpConnection::ParserPostParams() const
{
    return true;
}

bool BalHttpConnection::ParserCookies() const
{
    return true;
}

void BalHttpConnection::GetGetParamsField(const char*, std::string*) const
{

}

void BalHttpConnection::GetPostParamsField(const char*, std::string*) const
{

}

void BalHttpConnection::GetCookiesField(const char*, std::string*) const
{

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
    char statusStr[128] = {0};
    sprintf(statusStr, "%d %s\r\n", status, info);
    respondHttpHeadBuffer_ += statusStr;
}

void BalHttpConnection::RespondContentType(const char* type)
{
    if (type)
    {
        respondHttpHeadBuffer_ += "Content-Type: ";
        respondHttpHeadBuffer_ += type;
        respondHttpHeadBuffer_ += "\r\n";
    }
}

void BalHttpConnection::RespondContentLength(int length)
{
    respondHttpHeadBuffer_ += "Content-Length: ";
    char lengthStr[10] = {0};
    sprintf(lengthStr, "%d\r\n", length);
    respondHttpHeadBuffer_ += lengthStr;
}

void BalHttpConnection::RespondHeader(const char* field, const char* value)
{
    if (field && value)
    {
        respondHttpHeadBuffer_ += field;
        respondHttpHeadBuffer_ += ":";
        respondHttpHeadBuffer_ += value;
        respondHttpHeadBuffer_ += "\r\n";
    }
}

void BalHttpConnection::RespondHeaderComplete(bool keepalive)
{
    if (false == respondKeepAlive_)
    {
        RespondKeepAlive();
    }

    respondHttpHeadBuffer_ += "\r\n";
    std::string& buffer = respondHttpHeadBuffer_;
    WriteRawBuffer(buffer.c_str(), (uint32_t)buffer.length());
    respondHttpHeadBuffer_.clear();
}

void BalHttpConnection::RespondBody(const char* content, int size)
{
    WriteRawBuffer(content, (uint32_t)size);
}

void BalHttpConnection::RespondChunk(const char* content, int size)
{
    if (!content || 0 >= size) return;
    char chunkLengthStr[20] = {0};
    sprintf(chunkLengthStr, "\r\n%d\r\n", size);
    WriteRawBuffer(chunkLengthStr, (uint32_t)strlen(chunkLengthStr));
    WriteRawBuffer(content, size);
}

void BalHttpConnection::RespondChunkComplete()
{
    WriteRawBuffer("\r\n0\r\n", 5);
}

void BalHttpConnection::RespondComplete(bool close)
{
    if (false == requestKeepAlive_)
    {
        Close(false);
    }
    else if (true == close)
    {
        Close(false);
    }
}

void BalHttpConnection::RespondData(const char* buffer, int size, bool keepalive, bool close)
{
    if (!buffer || 0 == size) return;

    RespondBegin();
    RespondVersion(1, 0);
    RespondStatus(200, "ok");
    RespondContentLength(size);
    RespondHeaderComplete(keepalive);
    RespondBody(buffer, size);
    RespondComplete(close);
}

bool BalHttpConnection::WriteRawBuffer(const char* buffer, uint32_t size)
{
    if (StatusEstablish != status_) return false;
    if (nullptr_() == buffer || 0 == size || !httpServer_) return false;

    if (respondBuffer_.GetSize() <= 0)
    {
        bool closed = false;
        uint32_t writeSize = BalTcpSocket::WriteBuffer(buffer, size, &closed);

        if (closed)
        {
            DoCloseProcedure(false, true);
            return false;
        }
        else
        {
            respondBuffer_.AppendBuffer(buffer + writeSize, (size_t)(size - writeSize));
        }
    }
    else
    {
        respondBuffer_.AppendBuffer(buffer, (size_t)(size));
    }

    if (httpServer_->GetMaxWriteBufferSize() <= respondBuffer_.GetSize())
    {
        BalHandle<BalHttpConnection> conn(this, shareUserCount_);
        BalHandle<IBalHttpCallback> callback = httpServer_->GetCallback();
        if (callback && callback->IsCallable())
        {
            callback->OnWriteBufferFull(conn);
        }
    }
    else if (0 == respondBuffer_.GetSize())
    {
        BalHandle<BalHttpConnection> conn(this, shareUserCount_);
        BalHandle<IBalHttpCallback> callback = httpServer_->GetCallback();
        if (callback && callback->IsCallable())
        {
            callback->OnWriteBufferDrain(conn);
        }
    }
    return true;
}

bool BalHttpConnection::DoCloseProcedure(bool accord, bool delEvent)
{
    BalHandle<BalHttpConnection> conn(this, shareUserCount_);

    if (httpServer_)
    {
        BalHandle<BalEventLoop> eventLoop = httpServer_->GetEventLoop();
        if (eventLoop)
        {
            if (true == delEvent)
            {
                eventLoop->DeleteEventListener(eventHandle_, EventReadWrite);
            }
            eventLoop->RemoveTimer(0, timerCallbackPtr_.GetHandle());
        }

        BalHandle<BalElement> element
            = dynamic_cast_<BalHttpConnection, BalElement>(conn);
        if (element && eventLoop)
        {
            eventLoop->AddDelayReleaseElement(element);
        }
        httpServer_->EraseTcpConnection(GetFd());
    }

    BalTcpSocket::Close(); status_ = StatusClosed;
    BalHandle<IBalHttpCallback> callback = httpServer_->GetCallback();
    if (callback && callback->IsCallable())
    {
        callback->OnHttpClose(conn, accord);
    }
    return true;
}

void BalHttpConnection::OnTime(uint32_t id, BalHandle<BalTimer> timer)
{
    int64_t current = BootUtil::BalTimeStamp::GetCurrent();
    int64_t timeout = (int64_t)httpServer_->GetTimeout();
    if (current - lastReadTime_ >= timeout)
    {
        DoCloseProcedure(true, true);
    }
    else
    {
        uint32_t outTime = (uint32_t)(timeout - current + lastReadTime_);
        BalHandle<BalEventLoop> eventLoop = httpServer_->GetEventLoop();
        if (eventLoop)
        {
            eventLoop->SetTimerOut(0, timerCallbackPtr_.GetHandle(), outTime);
        }
    }
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

    bool closed = false;
    const int maxReadSize = 10240;
    char buffer[maxReadSize] = {0};
    BalEventCallbackEnum ret = EventRetContinue;
    uint32_t readSize = ReadBuffer(buffer, maxReadSize, &closed);

    if (closed)
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

    if (0 == readSize)
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
    if (0 == writeBuffer_.GetSize()) return EventRetComplete;

    bool closed = false;
    char* buffer = (char*)writeBuffer_.RawBuffer();
    uint32_t size = (uint32_t)writeBuffer_.GetSize();
    uint32_t writeSize = WriteBuffer(buffer, size, &closed);

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
    requestBuffer_.AppendBuffer(buffer, len);
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
            callback->OnHttpComplete(conn, requestBuffer_.RawBuffer(),
                (uint32_t)(requestBuffer_.GetSize()));
        }
    }

    requestBuffer_.Clear();
    requestBodySize_ = 0;
    currentChunkedSize_ = 0;
    requestKeepAlive_ = false;
    respondKeepAlive_ = false;
    respondChunked_ = false;
    return 0;
}

int BalHttpConnection::_OnChunkHeader(http_parser* parser)
{
    if (parser)
    {
        currentChunkedSize_ = (uint32_t)(parser->content_length);
    }
    requestBuffer_.Clear();
    return 0;
}

int BalHttpConnection::_OnChunkComplete(http_parser* parser)
{
    if (httpServer_)
    {
        BalHandle<IBalHttpCallback> callback = httpServer_->GetCallback();
        if (callback && callback->IsCallable())
        {
            BalHandle<BalHttpConnection> conn(this, shareUserCount_);
            callback->OnHttpChunkBuffer(conn, requestBuffer_.RawBuffer(),
                (uint32_t)(requestBuffer_.GetSize()));
        }
    }
    requestBuffer_.Clear();
    return 0;
}
