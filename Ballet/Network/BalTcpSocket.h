#ifndef Ballet_Network_BalTcpSocket_H
#define Ballet_Network_BalTcpSocket_H
#include "Common/BalInct.h"
#include "BalNetworkInct.h"
#include "BalSocket.h"

namespace Ballet
{
    namespace Network
    {
        class BalTcpSocket :public BalSocket
        {
        public:
            explicit BalTcpSocket(bool v6);

        public:
            bool Close() throw();
            bool Listen() throw();
            bool Accpet(int* id) throw();
            bool SetNoBlock() throw();
            bool ShutdownWrite() throw();
            bool SetNoDelay(bool set) throw();
            bool SetKeepAlive(bool set) throw();
            bool BindAddress(BalHandle<BalInetAddress> addr) throw();
        };
    }
}
#endif
