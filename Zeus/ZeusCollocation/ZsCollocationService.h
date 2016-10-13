#ifndef Zeus_ZeusCollocation_ZsCollocationService_H
#define Zeus_ZeusCollocation_ZsCollocationService_H
#include <Ballet/Common/BalInct.h>
#include <Ballet/Network/BalEventLoop.h>
#include <Ballet/ServiceWorker/BalServiceManage.h>
using namespace Ballet;
using namespace Network;
using namespace ServiceWorker;

#include <Zeus/ZeusBase/ZsDefine.h>
#include <Zeus/ZeusBase/ZsNodeTree.h>
#include <Libs/IniLoader/IniConfigLoader.h>
using namespace Libs;

#include "ZsClientServer.h"

namespace Zeus
{
    class ZsCollocationService
    {
    public:
        ZsCollocationService(const char*);

    public:
        void OnStart(BalHandle<BalService>);
        void OnServiceMain(BalHandle<BalService>);
        void OnReceiveSignal(int id, BalHandle<BalEventLoop> el);

    public:
        CBalServiceCallbackPtr<ZsCollocationService> callback_;

    private:
        std::string configFile_;
        BalHandle<BalEventLoop> eventLoop_;
        CBalSignalCallbackPtr<ZsCollocationService> signalCallback_;
    };
}
#endif
