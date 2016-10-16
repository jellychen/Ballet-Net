#ifndef Zeus_ZeusBroker_ZsCollocationClient_H
#define Zeus_ZeusBroker_ZsCollocationClient_H
#include <Ballet/Common/BalInct.h>
#include <Ballet/BootUtil/BalPerformance.h>
#include <Ballet/Network/BalInetAddress.h>
#include <Ballet/Network/BalEventLoop.h>
#include <Ballet/Network/BalTcpClient.h>
#include <Zeus/ZeusBase/ZsNodeTree.h>
#include <Zeus/ZeusBase/ZsClientProtocol.h>
#include <Zeus/ZeusBase/ZsClientData.h>
#include <Zeus/ZeusBase/ZsClientHeartbeat.h>
using namespace Ballet;
using namespace Network;
using namespace BootUtil;

namespace Zeus
{
    class ZsCollocationClient: public BalNoCoable
    {
    public:
        ZsCollocationClient(BalHandle<BalEventLoop>,
            uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);

    public:
        bool Start(BalHandle<ZsNodeTree>, BalHandle<BalInetAddress>);

    private:
        void OnTime(uint32_t, BalHandle<BalTimer>);
        void OnConnect(BalHandle<BalTcpClient> client, bool success);
        void OnReceive(BalHandle<BalTcpClient> client, const char* buffer, uint32_t len);
        void OnClose(BalHandle<BalTcpClient> client, bool accord);

    private:
        uint32_t heartbeatTime_;
        uint32_t timeoutTime_;
        uint32_t maxPackageSize_;
        uint32_t connectTimeout_;
        uint32_t maxReadBufferSize_;
        uint32_t maxWriteBufferSize_;
        ZsClientHeartbeat heartbeat_;
        BalHandle<ZsNodeTree> nodeTree_;
        BalHandle<BalEventLoop> eventLoop_;
        BalHandle<BalTcpClient> tcpClient_;
        BalHandle<BalInetAddress> tcpAddress_;
        BalHandle<IBalProtocol> tcpProtocol_;
        CBalTimerCallbackPtr<ZsCollocationClient> timerCallback_;
        CBalTcpClientCallbackPtr<ZsCollocationClient> tcpCallback_;
    };
}
#endif
