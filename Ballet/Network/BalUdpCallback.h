#ifndef Ballet_Network_BalUdpCallback_H
#define Ballet_Network_BalUdpCallback_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace Network
    {
        class BalUdpServer;
        struct IBalUdpCallback :public BalCallback
        {
            virtual void OnReceive(BalHandle<BalUdpServer>                      \
                server, const char* buffer, uint32_t len) =0;
        };

        BalCallbackSinkBegin(CBalUdpCallback)
        BalCallbackSink(void, OnReceive, (BalHandle<BalUdpServer> server,       \
                const char* buffer, uint32_t len), (server, buffer, len))
        BalCallbackSinkComplete()
        BalCallbackSinkPtrDefine(CBalUdpCallback, IBalUdpCallback)
    }
}
#endif
