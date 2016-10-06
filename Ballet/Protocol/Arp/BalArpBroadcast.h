#ifndef Ballet_Protocol_Arp_BalArpBroadcast_H
#define Ballet_Protocol_Arp_BalArpBroadcast_H
#include "Common/BalInct.h"
#include "Network/BalNetworkInct.h"

namespace Ballet
{
    namespace Protocol
    {
        class BalArpBroadcast: public BalNoCoable
        {
        public:
            BalArpBroadcast();
            virtual ~BalArpBroadcast();

        public:
            bool Broadcast(std::string ip, std::string mac) const;
            bool BroadcastHardware(std::string ip, std::string ethernet) const;

        private:
            bool BroadcastBinary(uint8_t ip[4], uint8_t mac[6]) const;

        private:
            int fd_;
        };
    }
}
#endif//Ballet_Protocol_Arp_BalArpAccord_H
