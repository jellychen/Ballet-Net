#ifndef Ballet_Network_BalSocket_H
#define Ballet_Network_BalSocket_H
#include "Common/BalInct.h"
#include "BalNetworkInct.h"
#include "BalInetAddress.h"

namespace Ballet
{
    namespace Network
    {
        class BalSocket :public BalNoCoable
        {
        public:
            explicit BalSocket(int fd);
            virtual ~BalSocket();

        public:
            int  GetFd() const {return fd_;}
            bool SetReuseAddr(bool set) throw();
            bool SetReusePort(bool set) throw();
            
        protected:
            int fd_;
        };
    }
}
#endif
