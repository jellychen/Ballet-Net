#include "ZsCollocationService.h"
using namespace std;
using namespace Zeus;

ZsCollocationService::ZsCollocationService(const char* file)
    :callback_(this), signalCallback_(this), eventLoop_(new BalEventLoop())
{
    configFile_ = file;
    callback_->HookOnStart(&ZsCollocationService::OnStart);
    callback_->HookOnServiceMain(&ZsCollocationService::OnServiceMain);
    signalCallback_->HookOnReceiveSignal(&ZsCollocationService::OnReceiveSignal);
}

void ZsCollocationService::OnStart(BalHandle<BalService>)
{

}

void ZsCollocationService::OnServiceMain(BalHandle<BalService>)
{
    IniConfigLoader loader;
    loader.LoadFile(configFile_.c_str());
    BalHandle<ZsNodeTree> nodeTree(new ZsNodeTree());

    // read config
    std::string clientPort = "";
    loader.GetItem(zsCollocationClientPortItemKey,
         &clientPort, zsDefaultCollocationClientPort);
    uint16_t clientPortNum = (uint16_t)atoi(clientPort.c_str());

    std::string maxPackage = "";
    loader.GetItem(zsCollocationClientMaxPackageItemKey,
         &clientPort, zsDefaultCollocationClientMaxPackage);
    uint32_t maxPackageNum = (uint32_t)atoi(maxPackage.c_str());

    std::string timeout = "";
    loader.GetItem(zsCollocationClientTimeoutItemKey,
         &timeout, zsDefaultCollocationClientTimeout);
    uint32_t timeouNum = (uint32_t)atoi(timeout.c_str());

    std::string maxReadBuffer = "";
    loader.GetItem(zsCollocationClientMaxReadBufferItemKey,
         &maxReadBuffer, zsDefaultCollocationClientMaxReadBuffer);
    uint32_t maxReadBufferNum = (uint32_t)atoi(maxReadBuffer.c_str());

    std::string maxWriteBuffer = "";
    loader.GetItem(zsCollocationClientMaxWriteBufferItemKey,
         &maxWriteBuffer, zsDefaultCollocationClientMaxWriteBuffer);
    uint32_t maxWriteBufferNum = (uint32_t)atoi(maxWriteBuffer.c_str());

    BalHandle<ZsClientServer> clientServer(
        new ZsClientServer(eventLoop_, maxPackageNum,
                timeouNum, maxReadBufferNum, maxWriteBufferNum)
    );

    if (clientServer)
    {
        BalHandle<BalInetAddress> udpAddress(
            new BalInetAddress(clientPortNum, false, false));
        clientServer->Start(nodeTree, udpAddress);
    }

    if (eventLoop_)
    {
        eventLoop_->SetSignalListener(BALSINGLETON_EXIT, signalCallback_);
    }
    eventLoop_->DoEventLoop();
}

void ZsCollocationService::OnReceiveSignal(int id, BalHandle<BalEventLoop> el)
{
    if (id == BALSINGLETON_EXIT && eventLoop_)
    {
        eventLoop_->DoExitEventLoop();
    }
}
