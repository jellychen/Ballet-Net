#ifndef Ballet_Network_BalUdpProtocol_H
#define Ballet_Network_BalUdpProtocol_H
#include "Common/BalInct.h"
#include "BalUdpChannel.h"

namespace Ballet
{
    namespace Network
    {
        class IBalUdpProtocol
        {
        public:
            virtual bool Encode(const char*, uint32_t,
                BalHandle<BalUdpChannel>, BalHandle<BalInetAddress> addr) =0;
            virtual bool Decode(const char*, uint32_t,
                BalHandle<BalUdpChannel>, BalHandle<BalInetAddress> addr) =0;
        };
    }
}
#endif
