#ifndef Ballet_Network_BalInetAddress_H
#define Ballet_Network_BalInetAddress_H
#include "Common/BalInct.h"
#include "BalNetworkInct.h"
#include "BalEndian.h"

namespace Ballet
{
    namespace Network
    {
        class BalInetAddress
        {
        public:
            BalInetAddress(struct sockaddr* addr);
            BalInetAddress(struct sockaddr_in& addr);
            BalInetAddress(struct sockaddr_in6& addrV6);
            explicit BalInetAddress(uint16_t port, bool lookback, bool v6);
            explicit BalInetAddress(const char* ip, uint16_t port, bool v6);
            explicit BalInetAddress(const char* address, bool v6);

        public:
            bool IsV6() const;
            void GetIp(std::string&) const;
            void GetAddressStr(std::string&) const;
            uint16_t GetPort() const;
            bool SetAddr(struct sockaddr* addr);
            struct sockaddr* GetSocketAddr() const;

        private:
            bool v6_;
            union
            {
                struct sockaddr_in addr_;
                struct sockaddr_in6 addrV6_;
            };
        };
    }
}
#endif
