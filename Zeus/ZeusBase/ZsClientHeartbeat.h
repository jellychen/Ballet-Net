#ifndef Zeus_ZeusBase_ZsClientHeartbeat_H
#define Zeus_ZeusBase_ZsClientHeartbeat_H
#include <Ballet/Common/BalInct.h>
using namespace Ballet;

#include "ZsClientData.h"

namespace Zeus
{
    class ZsClientHeartbeat
    {
    public:
        ZsClientHeartbeat();

    public:
        std::string heartbeatBuffer_;
    };
}
#endif
