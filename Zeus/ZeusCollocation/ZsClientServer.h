#ifndef Zeus_ZeusCollocation_ZsClientServer_H
#define Zeus_ZeusCollocation_ZsClientServer_H
#include <Ballet/Common/BalInct.h>
#include <Ballet/BootUtil/BalPerformance.h>
#include <Ballet/Network/BalEventLoop.h>
#include <Ballet/Network/BalTcpServer.h>
#include <Zeus/ZeusBase/ZsNodeTree.h>
#include <Zeus/ZeusBase/ZsClientProtocol.h>
#include <Zeus/ZeusBase/ZsClientData.h>
#include <Zeus/ZeusBase/ZsClientHeartbeat.h>
using namespace Ballet;
using namespace Network;
using namespace BootUtil;

#include "ZsClientServer.h"
#include "ZsCollocationNodeData.h"

namespace Zeus
{
    class ZsClientServer: public BalNoCoable
    {
    public:
        ZsClientServer(BalHandle<BalEventLoop>, uint32_t, uint32_t, uint32_t, uint32_t);

    public:
        bool Start(BalHandle<ZsCollocationNodeData>, BalHandle<BalInetAddress>);

    private:
        void OnConnect(BalHandle<BalTcpConnection> conn, bool success);
        void OnClose(BalHandle<BalTcpConnection> conn, bool accord);
        void OnReceive(BalHandle<BalTcpConnection> conn, const char* buffer, uint32_t len);

    private:
        ZsClientHeartbeat heartbeat_;
        BalHandle<BalTcpServer> tcpServer_;
        BalHandle<ZsCollocationNodeData> nodeTree_;
        CBalTcpCallbackPtr<ZsClientServer> tcpCallback_;
    };
}
#endif
