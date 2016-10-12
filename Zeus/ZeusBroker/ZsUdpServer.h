#ifndef Zeus_ZeusBroker_ZsUdpServer_H
#define Zeus_ZeusBroker_ZsUdpServer_H
#include <Ballet/Common/BalInct.h>
#include <Ballet/Network/BalInetAddress.h>
#include <Ballet/Network/BalEventLoop.h>
#include <Ballet/Network/BalUdpServer.h>
using namespace Ballet;
using namespace Network;

#include "ZsNodeTree.h"

namespace Zeus
{
    class ZsUdpServer: public BalNoCoable
    {
    public:
        ZsUdpServer(BalHandle<BalEventLoop>);

    public:
        bool Start(BalHandle<ZsNodeTree>, BalHandle<BalInetAddress>);

    public:
        void OnReceive(BalHandle<BalUdpServer>, const char*, uint32_t, BalHandle<BalInetAddress>);

    private:
        BalHandle<ZsNodeTree> nodeTree_;
        CBalUdpCallbackPtr<ZsUdpServer> callback_;
    };
}
#endif
