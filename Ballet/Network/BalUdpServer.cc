#include "BalNetDefine.h"
#include "BalUdpServer.h"
using namespace Ballet;
using namespace Network;
#define BALUDP_MAXREAD_SIZE 10240

BalUdpServer::BalUdpServer(bool v6, BalHandle<BalEventLoop> eventLoop,
    BalHandle<IBalUdpProtocol> protocol, uint32_t maxPackage,
    BalHandle<IBalUdpCallback> callback)
    :BalUdpSocket(v6), eventCallbackPtr_(this), eventHandle_(GetFd())
{
    callback_ = callback;
    eventLoop_ = eventLoop;
    udpProtocol_ = protocol;
    maxPackage_ = maxPackage;
    detachFromEventLoop_ = false;

    if (!callback_ || !callback_->IsCallable() || !udpProtocol_)
    {
        throw std::runtime_error("BalUdpServer Construct Failed!@1");
    }

    if (!eventLoop_ || !eventCallbackPtr_ || !SetNoBlock())
    {
        throw std::runtime_error("BalUdpServer Construct Failed!@2");
    }
    else
    {
        eventCallbackPtr_->HookShouldRead(&BalUdpServer::ShoudRead);
        eventLoop_->SetEventListener(eventHandle_, EventRead, eventCallbackPtr_);
    }
}

BalUdpServer::~BalUdpServer()
{
    if (eventLoop_ && !detachFromEventLoop_)
    {
        eventLoop_->DeleteEventListener(eventHandle_, EventRead);
    }
}

bool BalUdpServer::IsV6()
{
    return BalUdpSocket::IsV6Socket();
}

bool BalUdpServer::Close()
{
    if (eventLoop_)
    {
        eventLoop_->DeleteEventListener(eventHandle_, EventRead);
    }
    detachFromEventLoop_ = true;
    return BalUdpSocket::Close();
}

bool BalUdpServer::Start(BalHandle<BalInetAddress> addr)
{
    return BindAddress(addr);
}

uint32_t BalUdpServer::GetMaxPackageSize() const
{
    return maxPackage_;
}

BalHandle<BalEventLoop> BalUdpServer::GetEventLoop() const
{
    return eventLoop_;
}

BalHandle<IBalUdpProtocol> BalUdpServer::GetProtocol() const
{
    return udpProtocol_;
}

BalHandle<IBalUdpCallback> BalUdpServer::GetCallback() const
{
    return callback_;
}

bool BalUdpServer::WriteBuffer(const char* buffer, uint32_t len, BalHandle<BalInetAddress> addr)
{
    if (!buffer || 0 == len || !addr) return false;
    if (udpProtocol_)
    {
        BalHandle<BalUdpServer> server(this, shareUserCount_);
        BalHandle<BalUdpChannel> channel =
            dynamic_cast_<BalUdpServer, BalUdpChannel>(server);
        return udpProtocol_->Encode(buffer, len, channel, addr);
    }
    return false;
}

bool BalUdpServer::WriteRawBuffer(const char* buffer, uint32_t len, BalHandle<BalInetAddress> addr)
{
    if (!buffer || 0 == len || !addr) return false;
    BalUdpSocket::SendBufferTo(buffer, len, addr);
    return true;
}

bool BalUdpServer::OnReceiveBuffer(const char* buffer, uint32_t len, BalHandle<BalInetAddress> addr)
{
    if (callback_ && callback_->IsCallable())
    {
        BalHandle<BalUdpServer> server(this, shareUserCount_);
        BalHandle<BalUdpChannel> channel =
            dynamic_cast_<BalUdpServer, BalUdpChannel>(server);
        callback_->OnReceive(server, buffer, len, addr);
    }
    return true;
}

BalEventCallbackEnum BalUdpServer::ShoudRead(int id, BalHandle<BalEventLoop> el)
{
    BalHandle<BalInetAddress> addr(new BalInetAddress(nullptr_()));
    char buffer[BALUDP_MAXREAD_SIZE] = {0};
    int readSize = BalUdpSocket::ReadBufferFrom(buffer, BALUDP_MAXREAD_SIZE, addr);
    if (readSize <= (int)(maxPackage_) && readSize > 0 && udpProtocol_)
    {
        BalHandle<BalUdpServer> server(this, shareUserCount_);
        BalHandle<BalUdpChannel> channel =
            dynamic_cast_<BalUdpServer, BalUdpChannel>(server);
        udpProtocol_->Decode(buffer, readSize, channel, addr);
    }
    return EventRetComplete;
}
