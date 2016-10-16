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
            int  GetFd() const{return fd_;}
            bool IsV6Socket() const;
            bool SetReuseAddr(bool set) throw();
            bool SetReusePort(bool set) throw();

        protected:
            uint32_t ReadBuffer(char* buffer, uint32_t, bool* close) const;
            uint32_t WriteBuffer(const char* buffer, uint32_t, bool* close) const;

        protected:
            int fd_;
        };
    }
}
#endif
