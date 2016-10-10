#ifndef Ballet_Network_BalUdpSocket_H
#define Ballet_Network_BalUdpSocket_H
#include "Common/BalInct.h"
#include "BalNetworkInct.h"
#include "BalSocket.h"

namespace Ballet
{
    namespace Network
    {
        class BalUdpSocket :public BalSocket
        {
        public:
            explicit BalUdpSocket(int fd);
            explicit BalUdpSocket(bool v6);

        public:
            bool Close() throw();
            bool SetNoBlock() throw();
            bool BindAddress(BalHandle<BalInetAddress> addr) throw();
            int  ReadBufferFrom(char*, uint32_t, BalHandle<BalInetAddress>& addr) throw();
            int  SendBufferTo(const char*, uint32_t, BalHandle<BalInetAddress> addr) throw();
        };
    }
}
#endif
