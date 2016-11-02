#ifndef Zeus_ZeusCollocation_ZsNodeServer_ZsNodeMember_H
#define Zeus_ZeusCollocation_ZsNodeServer_ZsNodeMember_H
#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalHandle.h>
#include <Ballet/Network/BalEventLoop.h>
#include <Ballet/Network/BalTcpClient.h>
#include <Libs/LoTrace/LoTrace.h>
using namespace Ballet;
using namespace Network;

#include "ZsNodeContext.h"

namespace Zeus
{
    class ZsNodeMember: public BalNoCoable
    {
    public:
        ZsNodeMember(BalHandle<ZsNodeContext> context);
        virtual ~ZsNodeMember();

    private:
        BalHandle<ZsNodeContext> context_;
    };
}
#endif
