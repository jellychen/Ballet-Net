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
            explicit BalTcpSocket(int fd);
            explicit BalTcpSocket(bool v6);
            virtual ~BalTcpSocket();

        public:
            bool Close() throw();
            bool Listen() throw();
            bool Accpet(int* id) throw();
            bool SetNoBlock() throw();
            bool ShutdownWrite() throw();
            bool SetNoDelay(bool set) throw();
            bool SetKeepAlive(bool set) throw();
            bool SetShutdownWriteWhenClose(bool set) throw();
            bool BindAddress(BalHandle<BalInetAddress> addr) throw();
            bool Connect(BalHandle<BalInetAddress> addr, bool* connecting) throw();

        public:
            bool Swap(BalTcpSocket& socket);
            
        private:
            bool shutdownWriteWhenClose_;
        };
    }
}
#endif
