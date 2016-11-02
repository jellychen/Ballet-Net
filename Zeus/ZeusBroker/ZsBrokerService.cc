#include "ZsBrokerService.h"
using namespace std;
using namespace Zeus;

ZsBrokerService::ZsBrokerService(const char* file)
    :callback_(this), signalCallback_(this), eventLoop_(new BalEventLoop())
{
    configFile_ = file;
    callback_->HookOnStart(&ZsBrokerService::OnStart);
    callback_->HookOnServiceMain(&ZsBrokerService::OnServiceMain);
    signalCallback_->HookOnReceiveSignal(&ZsBrokerService::OnReceiveSignal);
}

void ZsBrokerService::OnStart(BalHandle<BalService>)
{

}

void ZsBrokerService::OnServiceMain(BalHandle<BalService>)
{
    IniConfigLoader loader;
    loader.LoadFile(configFile_.c_str());
    BalHandle<ZsNodeTree> nodeTree(new ZsNodeTree());

    // server
    std::string brokerPort = "";
    loader.GetItem(zsBrokerPortItemKey, &brokerPort, zsDefaultBrokerPort);
    BalHandle<ZsUdpServer> udpServer(new ZsUdpServer(eventLoop_));
    if (udpServer)
    {
        int port = atoi(brokerPort.c_str());
        BalHandle<BalInetAddress> udpAddress(
            new BalInetAddress((uint16_t)port, true, false));
        udpServer->Start(nodeTree, udpAddress);
    }

    if (eventLoop_)
    {
        eventLoop_->SetSignalListener(BALSINGLETON_EXIT, signalCallback_);
    }
    eventLoop_->DoEventLoop();
}

void ZsBrokerService::OnReceiveSignal(int id, BalHandle<BalEventLoop> el)
{
    if (id == BALSINGLETON_EXIT && eventLoop_)
    {
        eventLoop_->DoExitEventLoop();
    }
}
