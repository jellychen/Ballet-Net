#ifndef Zeus_ZeusCollocation_ZsNodeServer_ZsNodeContext_H
#define Zeus_ZeusCollocation_ZsNodeServer_ZsNodeContext_H
#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalHandle.h>
#include <Ballet/Network/BalEventLoop.h>
using namespace Ballet;
using namespace Network;

#include "ZsWorkboard/ZsWorkboardOptions.h"

namespace Zeus
{
    class ZsNodeContext: public BalNoCoable
    {
    public:
        ZsNodeContext(BalHandle<ZsWorkboardOptions> options);

    public:
        bool StartDoEvent() const;

    public:
        BalHandle<BalEventLoop> eventLoop_;
        BalHandle<ZsWorkboardOptions> options_;
    };
}
#endif
