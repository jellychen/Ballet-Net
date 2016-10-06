#include "BalNetDefine.h"
#include "BalUdpServer.h"
using namespace Ballet;
using namespace Network;

BalUdpServer::BalUdpServer(bool v6, BalHandle<BalEventLoop> eventLoop,
    BalHandle<IBalProtocol> protocol, uint32_t maxPackage,
    BalHandle<IBalUdpCallback> callback):BalUdpSocket(v6)
{
    udpProtocol_ = protocol;
    eventLoop_ = eventLoop;

}

BalUdpServer::~BalUdpServer()
{

}

bool BalUdpServer::IsV6()
{
    return true;
}

bool BalUdpServer::Close()
{
    return true;
}

bool BalUdpServer::Start(BalHandle<BalInetAddress> addr)
{
    return true;
}

uint32_t BalUdpServer::GetTimeout() const
{
    return true;
}

uint32_t BalUdpServer::GetMaxPackageSize() const
{
    return true;
}

BalHandle<BalEventLoop> BalUdpServer::GetEventLoop() const
{
    return eventLoop_;
}

BalHandle<IBalProtocol> BalUdpServer::GetProtocol() const
{
    return udpProtocol_;
}

BalHandle<IBalUdpCallback> BalUdpServer::GetCallback() const
{
    return callback_;
}
