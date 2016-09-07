#ifndef Ballet_Network_BalProtocol_H
#define Ballet_Network_BalProtocol_H
#include "Common/BalInct.h"
#include "BalChannel.h"

namespace Ballet
{
    namespace Network
    {
        enum BalProtocolStatus
        {
            StatusSuccess   = 0,
            StatusFail      = 1,
            StatusNoEnough  = 2,
        };

        class IBalProtocol
        {
        public:
            virtual BalProtocolStatus CalSize(const char*, uint32_t, uint32_t*) =0;
            virtual bool Encode(const char*, uint32_t, BalHandle<BalChannel>) =0;
            virtual bool Decode(const char*, uint32_t, BalHandle<BalChannel>) =0;
        };
    }
}
#endif
