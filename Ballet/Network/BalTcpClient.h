#ifndef Ballet_Network_BalTcpClient_H
#define Ballet_Network_BalTcpClient_H
#include "Common/BalInct.h"
#include "BalNetworkInct.h"
#include "BalTcpSocket.h"
#include "BalEventLoop.h"

namespace Ballet
{
    namespace Network
    {
        class BalTcpClient :public BalElement, public BalNoCoable
        {
        public:
            BalTcpClient(BalHandle<BalEventLoop> eventLoop);

        public:
            bool BindAddress(const BalInetAddress* addr) throw();
            
        protected:
            BalWeakHandle<BalEventLoop> eventLoop_;
        };
    }
}
#endif
