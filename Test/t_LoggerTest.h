
#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalHandle.h>
#include <Ballet/Network/BalEventLoop.h>
#include <Ballet/Network/BalTcpServer.h>
#include <Ballet/Network/BalNetworkInct.h>
#include <Ballet/Protocol/Arp/BalArpBroadcast.h>
#include <Ballet/Protocol/Arp/BalArpBroadcast.h>
#include <Libs/LoTrace/LoTrace.h>
using namespace Ballet;
using namespace Libs;
using namespace Logger;

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

using namespace BootUtil;
using namespace Network;
using namespace Protocol;

void t_Logger_main()
{
    LoTraceInit();
    LoTraceFile("1.txt");
    LoTraceWriteThread();
    for (int i = 0; i < 100000; ++i)
    {
        __LOG_DEBUG__("asdads%dasdads", 10);
    }
    LoTraceWaitClose(200);
}
