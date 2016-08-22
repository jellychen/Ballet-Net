#ifndef Ballet_Network_BalTcpCallback_H
#define Ballet_Network_BalTcpCallback_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace Network
    {
        class BalTcpConnection;

        struct IBalTcpCallback :public BalCallback
        {
            // note: call
            virtual void OnConnect(BalHandle<BalTcpConnection> conn, bool success);

            // note: call when fd close
            virtual void OnClose(BalHandle<BalTcpConnection> conn);

            //  note: call when fd read package
            virtual void OnReceive(BalHandle<BalTcpConnection> conn, uint8_t* buffer, uint32_t len);
        };
    }
}
#endif
