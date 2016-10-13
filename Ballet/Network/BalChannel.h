#ifndef Ballet_Network_BalChannel_H
#define Ballet_Network_BalChannel_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace Network
    {
        class BalChannel
        {
        public:
            virtual bool WriteRawBuffer(const char* buffer, uint32_t len) =0;
            virtual bool OnReceiveBuffer(const char* buffer, uint32_t len) =0;
            virtual bool BroadcastRawBuffer(const char* buffer, uint32_t len) =0;
        };
    }
}
#endif
