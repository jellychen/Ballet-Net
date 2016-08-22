#include "BalTcpClient.h"
using namespace Ballet::Network;

BalTcpClient::BalTcpClient(BalHandle<BalEventLoop> eventLoop)
{
    if (!eventLoop)
    {
        throw std::runtime_error("BalTcpClient Construct Failed!");
    }
    eventLoop_ = eventLoop;
}
