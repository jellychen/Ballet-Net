#ifndef Ballet_Network_BalUdpChannel_H
#define Ballet_Network_BalUdpChannel_H
#include "Common/BalInct.h"
#include "BalInetAddress.h"

namespace Ballet
{
    namespace Network
    {
        class BalUdpChannel
        {
        public:
            virtual bool WriteRawBuffer(const char* buffer,
                    uint32_t len, BalHandle<BalInetAddress> addr) =0;
            virtual bool OnReceiveBuffer(const char* buffer,
                    uint32_t len, BalHandle<BalInetAddress> addr) =0;
        };
    }
}
#endif
