#ifndef Zeus_ZeusBroker_ZsBrokerService_H
#define Zeus_ZeusBroker_ZsBrokerService_H
#include <Ballet/Common/BalInct.h>
#include <Ballet/Network/BalEventLoop.h>
#include <Ballet/ServiceWorker/BalServiceManage.h>
using namespace Ballet;
using namespace Network;
using namespace ServiceWorker;

#include <Zeus/ZeusInclude/ZsDefine.h>
#include <Libs/IniLoader/IniConfigLoader.h>
using namespace Libs;

#include "ZsNodeTree.h"
#include "ZsUdpServer.h"

namespace Zeus
{
    class ZsBrokerService
    {
    public:
        ZsBrokerService(const char*);

    public:
        void OnStart(BalHandle<BalService>);
        void OnServiceMain(BalHandle<BalService>);
        void OnReceiveSignal(int id, BalHandle<BalEventLoop> el);

    public:
        CBalServiceCallbackPtr<ZsBrokerService> callback_;

    private:
        std::string configFile_;
        BalHandle<BalEventLoop> eventLoop_;
        CBalSignalCallbackPtr<ZsBrokerService> signalCallback_;
    };
}
#endif
