#include "BalNetDefine.h"
#include "BalTcpServer.h"
using namespace Ballet;
using namespace Network;

BalTcpServer::BalTcpServer(bool v6, BalHandle<BalEventLoop> eventLoop,
    BalHandle<IBalProtocol> protocol, uint32_t maxPackage,
    BalHandle<IBalTcpCallback> callback, uint32_t timeout,
    uint32_t maxReadBufferSize, uint32_t maxWriteBufferSize)
    :BalTcpSocket(v6),eventCallbackPtr_(this)
{
    protocol_ = protocol;
    eventLoop_ = eventLoop;
    maxTimeout_ = timeout;
    maxPackageSize_ = maxPackage;
    maxReadBufferSize_ = maxReadBufferSize;
    maxWriteBufferSize_ = maxWriteBufferSize;

    if (!callback || !callback->IsCallable() || !timeout || !protocol_)
    {
        throw std::runtime_error("BalTcpServer Construct Failed");
    }
    else
    {
        tcpCallback_ = callback;
    }

    if (!eventLoop_ || !eventCallbackPtr_ || !SetNoBlock())
    {
        throw std::runtime_error("BalTcpServer Construct Failed");
    }
    else
    {
        eventCallbackPtr_->HookShouldRead(&BalTcpServer::ShoudAccept);
        eventLoop_->SetEventListener(GetFd(), EventRead, eventCallbackPtr_);
    }
}

bool BalTcpServer::IsV6()
{
    return BalTcpSocket::IsV6Socket();
}

bool BalTcpServer::Close()
{
    if (eventLoop_)
    {
        eventLoop_->DeleteEventListener(GetFd(), EventRead);
    }
    return BalTcpSocket::Close();
}

bool BalTcpServer::Start(BalHandle<BalInetAddress> addr)
{
    if (false == BindAddress(addr)) return false;
    if (false == Listen()) return false;
    return true;
}

uint32_t BalTcpServer::GetTimeout() const
{
    return maxTimeout_;
}

uint32_t BalTcpServer::GetMaxReadBufferSize() const
{
    return maxReadBufferSize_;
}

uint32_t BalTcpServer::GetMaxWriteBufferSize() const
{
    return maxWriteBufferSize_;
}

BalHandle<BalEventLoop> BalTcpServer::GetEventLoop() const
{
    return eventLoop_;
}

BalHandle<IBalProtocol> BalTcpServer::GetProtocol() const
{
    return protocol_;
}

BalHandle<IBalTcpCallback> BalTcpServer::GetCallback() const
{
    return tcpCallback_;
}

bool BalTcpServer::EraseTcpConnection(int id)
{
    std::cout<<"BalTcpServer::EraseTcpConnection "<<id<<std::endl;
    mapConnPoolT::iterator iter = mapConnPool_.find(id);
    if (mapConnPool_.end() != iter)
    {
        mapConnPool_.erase(iter);
    }
    return true;
}

BalEventCallbackEnum BalTcpServer::ShoudAccept(int id, BalHandle<BalEventLoop> el)
{
    std::cout<<"BalTcpServer::ShoudAccept"<<std::endl;

    int accpetId = 0;
    if (!BalTcpSocket::Accpet(&accpetId))
    {
        std::cout<<"BalTcpServer::ShoudAccept EventRetComplete"<<std::endl;
        return EventRetComplete;
    }

    try
    {
        BalHandle<BalTcpServer> server(this, shareUserCount_);
        BalHandle<BalTcpConnection> conn(new BalTcpConnection(accpetId, server));
        if (conn)
        {
            mapConnPool_[accpetId] = conn;
            conn->SetNoDelay(true); conn->SetReuseAddr(true);
            if (tcpCallback_ && tcpCallback_->IsCallable())
            {
                tcpCallback_->OnConnect(conn, true);
            }
        }
    }
    catch (std::exception&)
    {
        std::cout<<"BalTcpServer::ShoudAccept exception"<<std::endl;
    }

    std::cout<<"BalTcpServer::ShoudAccept end "<< accpetId <<std::endl;
    return EventRetContinue;
}
