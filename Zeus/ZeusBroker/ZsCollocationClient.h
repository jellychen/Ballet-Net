#ifndef Zeus_ZeusBroker_ZsCollocationClient_H
#define Zeus_ZeusBroker_ZsCollocationClient_H
#include <Ballet/Common/BalInct.h>
#include <Ballet/Network/BalInetAddress.h>
#include <Ballet/Network/BalEventLoop.h>
#include <Ballet/Network/BalTcpClient.h>
using namespace Ballet;
using namespace Network;

#include "ZsNodeTree.h"

namespace Zeus
{
    class ZsCollocationClient: public BalNoCoable
    {
    public:
        ZsCollocationClient(BalHandle<BalEventLoop>);

    public:
        bool Start(BalHandle<ZsNodeTree>, BalHandle<BalInetAddress>);

    private:
        BalHandle<ZsNodeTree> nodeTree_;
    };
}
#endif
