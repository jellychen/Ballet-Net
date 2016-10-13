#ifndef Zeus_ZeusBase_ZsClientProtocol_H
#define Zeus_ZeusBase_ZsClientProtocol_H
#include <Ballet/Common/BalInct.h>
#include <Ballet/Network/BalInetAddress.h>
#include <Ballet/Network/BalProtocol.h>
using namespace Ballet;
using namespace Network;

namespace Zeus
{
    class ZsClientProtocol: public IBalProtocol
    {
    public:
        BalProtocolStatus CalSize(const char*, uint32_t, uint32_t*);
        virtual bool Encode(const char*, uint32_t, BalHandle<BalChannel>);
        virtual bool Decode(const char*, uint32_t, BalHandle<BalChannel>);
    };
}
#endif
