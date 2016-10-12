#include "ZsUdpServer.h"
using namespace Zeus;

ZsUdpServer::ZsUdpServer(BalHandle<BalEventLoop>):callback_(this)
{

}

bool ZsUdpServer::Start(BalHandle<ZsNodeTree>, BalHandle<BalInetAddress>)
{
    return true;
}

void ZsUdpServer::OnReceive(BalHandle<BalUdpServer>, const char*, uint32_t, BalHandle<BalInetAddress>)
{

}
