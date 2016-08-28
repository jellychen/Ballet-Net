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
            virtual void OnConnect(BalHandle<BalTcpConnection> conn, bool success) =0;

            // note: call when fd close
            virtual void OnClose(BalHandle<BalTcpConnection> conn) =0;

            //  note: call when fd read package
            virtual void OnReceive(BalHandle<BalTcpConnection> conn, uint8_t* buffer, uint32_t len) =0;
        };
    }
}
#endif
