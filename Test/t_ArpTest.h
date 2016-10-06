
#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalHandle.h>
#include <Ballet/Network/BalEventLoop.h>
#include <Ballet/Network/BalTcpServer.h>
#include <Ballet/Protocol/Arp/BalArpBroadcast.h>
using namespace Ballet;

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

using namespace BootUtil;
using namespace Network;
using namespace Protocol;

void t_Art_main()
{
    BalHandle<BalArpBroadcast> arp(new BalArpBroadcast());
    arp->Broadcast("127.0.0.1", "ac:bc:32:a8:f0:eb");
    
}
