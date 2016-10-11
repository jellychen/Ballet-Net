#ifndef Ballet_Protocol_Lfv_BalLfvProtocol_H
#define Ballet_Protocol_Lfv_BalLfvProtocol_H
#include "Common/BalInct.h"
#include "Network/BalProtocol.h"
#include "Network/BalEndian.h"

namespace Ballet
{
    using namespace Network;

    namespace Protocol
    {
        class BalLfvProtocol: public IBalProtocol
        {
        public:
            virtual BalProtocolStatus CalSize(const char*, uint32_t, uint32_t*) =0;
            virtual bool Encode(const char*, uint32_t, BalHandle<BalChannel>) =0;
            virtual bool Decode(const char*, uint32_t, BalHandle<BalChannel>) =0;
        };
    }
}
#endif
