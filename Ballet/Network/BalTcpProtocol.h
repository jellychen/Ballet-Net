#ifndef Ballet_Network_BalTcpProtocol_H
#define Ballet_Network_BalTcpProtocol_H
#include "Common/BalInct.h"
#include "BalTcpConnection.h"

namespace Ballet
{
    namespace Network
    {
        enum BalTcpProtocolStatusEnum
        {
            StatusSuccess   = 0,
            StatusFail      = 1,
            StatusNoEnough  = 2,
        };

        class IBalTcpProtocol
        {
        public:
            virtual BalTcpProtocolStatusEnum CalSize(const char*, uint32_t) =0;
            virtual bool Encode(const char*, uint32_t, BalHandle<BalTcpConnection>) =0;
            virtual bool Decode(const char*, uint32_t, BalHandle<BalTcpConnection>) =0;
        };
    }
}
#endif
