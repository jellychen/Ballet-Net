#ifndef Ballet_Network_BalTcpConnection_H
#define Ballet_Network_BalTcpConnection_H
#include "Common/BalInct.h"
#include "BalNetworkInct.h"
#include "BalTcpSocket.h"
#include "BalEventLoop.h"

namespace Ballet
{
    namespace Network
    {
        class BalTcpConnection :public BalElement, public BalNoCoable
        {
        public:
            BalTcpConnection(BalHandle<BalEventLoop> eventLoop);
            
        public:

        protected:
            BalWeakHandle<BalEventLoop> eventLoop_;
        };
    }
}
#endif
