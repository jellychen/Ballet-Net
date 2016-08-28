#include "BalTcpClient.h"
using namespace Ballet;
using namespace Ballet::Network;

BalTcpClient::BalTcpClient(BalHandle<BalEventLoop> eventLoop)
{
    if (!eventLoop)
    {
        throw std::runtime_error("BalTcpClient Construct Failed!");
    }
    eventLoop_ = eventLoop;
}

bool BalTcpClient::Connect(BalHandle<BalInetAddress> addr) throw()
{
    return true;
}

bool BalTcpClient::BindAddress(BalHandle<BalInetAddress> addr) throw()
{
    return true;
}
