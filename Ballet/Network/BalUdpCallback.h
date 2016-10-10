#ifndef Ballet_Network_BalUdpCallback_H
#define Ballet_Network_BalUdpCallback_H
#include "Common/BalInct.h"
#include "BalInetAddress.h"

namespace Ballet
{
    namespace Network
    {
        class BalUdpServer;
        struct IBalUdpCallback :public BalCallback
        {
            virtual void OnReceive(BalHandle<BalUdpServer> server, const char*      \
                buffer, uint32_t len, BalHandle<BalInetAddress> addr) =0;
        };

        BalCallbackSinkBegin(CBalUdpCallback)
        BalCallbackSink(void, OnReceive, (BalHandle<BalUdpServer> server,           \
                const char* buffer, uint32_t len, BalHandle<BalInetAddress> addr),  \
                (server, buffer, len, addr))
        BalCallbackSinkComplete()
        BalCallbackSinkPtrDefine(CBalUdpCallback, IBalUdpCallback)
    }
}
#endif
