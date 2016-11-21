#ifndef Zeus_ZeusCollocation_ZsNodeServer_ZsNodeMember_H
#define Zeus_ZeusCollocation_ZsNodeServer_ZsNodeMember_H
#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalHandle.h>
#include <Ballet/Network/BalEventLoop.h>
#include <Ballet/Network/BalTcpClient.h>
#include <Ballet/BootUtil/BalTimer.h>
#include <Ballet/BootUtil/BalTimeStamp.h>
using namespace Ballet;
using namespace Network;
using namespace BootUtil;

#include "ZsNodeContext.h"
#include "ZsNodeNetProtocol.h"

namespace Zeus
{
    class ZsNodeMember: public BalNoCoable
    {
    public:
        ZsNodeMember(BalHandle<ZsNodeContext>, BalHandle<BalInetAddress>);
        virtual ~ZsNodeMember();

    public:
        bool SendBuffer(const char* buffer, uint32_t len);

    private:
        bool Connect();
        bool CaseTimeoutReconnect();
        void OnTime(uint32_t, BalHandle<BalTimer>);
        void OnConnect(BalHandle<BalTcpClient> client, bool success);
        void OnClose(BalHandle<BalTcpClient> client, bool accord);
        void OnReceive(BalHandle<BalTcpClient> client, const char* buffer, uint32_t len);

    private:
        int64_t connetTime_;
        BalHandle<ZsNodeContext> context_;
        BalHandle<BalTcpClient> tcpClient_;
        BalHandle<BalInetAddress> connectAddr_;
        CBalTimerCallbackPtr<ZsNodeMember> timerCallback_;
        CBalTcpClientCallbackPtr<ZsNodeMember> clientCallback_;
    };
}
#endif
