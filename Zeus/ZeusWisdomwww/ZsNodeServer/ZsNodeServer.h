#ifndef Zeus_ZeusCollocation_ZsNodeServer_ZsNodeServer_H
#define Zeus_ZeusCollocation_ZsNodeServer_ZsNodeServer_H
#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalHandle.h>
#include <Ballet/Network/BalEventLoop.h>
#include <Ballet/Network/BalTcpServer.h>
#include <Zeus/ZeusBase/ZsClientProtocol.h>
using namespace Ballet;
using namespace Network;

#include "ZsNodeVote.h"
#include "ZsNodeCommand.h"
#include "ZsNodeContext.h"
#include "ZsNodeAddEntries.h"

namespace Zeus
{
    class ZsNodeServer: public BalNoCoable
    {
        typedef BalHandle<BalTcpConnection> TConn;
    public:
        ZsNodeServer(bool v6, BalHandle<BalEventLoop> eventLoop,
            uint32_t maxPackage, uint32_t maxReadBufferSize,
            uint32_t maxWriteBufferSize, uint32_t timeout);
        virtual ~ZsNodeServer();

    public:
        bool Start(BalHandle<BalInetAddress> addr);
        bool OnConnect(TConn conn, bool success);
        void OnReceive(TConn conn, const char* buffer, uint32_t len);

    private:
        void OnVoteRequest(TConn conn, const char* buffer, uint32_t len);
        void OnAddEntriesRequest(TConn conn, const char* buffer, uint32_t len);

    private:
        BalHandle<BalTcpServer> server_;
        BalHandle<BalEventLoop> eventLoop_;
        CBalTcpCallbackPtr<ZsNodeServer> callback_;
    };
}
#endif
