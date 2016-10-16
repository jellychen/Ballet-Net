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

    // client
    std::string maxPackage = "";
    loader.GetItem(zsCollocationClientMaxPackageItemKey,
         &maxPackage, zsDefaultCollocationClientMaxPackage);
    uint32_t maxPackageNum = (uint32_t)atoi(maxPackage.c_str());

    std::string heartbeat = "";
    loader.GetItem(zsCollocationClientHeartbeatItemKey,
         &heartbeat, zsDefaultCollocationClientHeartbeat);
    uint32_t heartbeatNum = (uint32_t)atoi(heartbeat.c_str());

    std::string timeout = "";
    loader.GetItem(zsCollocationClientTimeoutItemKey,
         &timeout, zsDefaultCollocationClientTimeout);
    uint32_t timeoutNum = (uint32_t)atoi(timeout.c_str());

    std::string connetTimeout = "";
    loader.GetItem(zsCollocationClientConnectTimeoutItemKey,
         &connetTimeout, zsDefaultCollocationClientConnectTimeout);
    uint32_t connetTimeoutNum = (uint32_t)atoi(connetTimeout.c_str());

    std::string maxReadBuffer = "";
    loader.GetItem(zsCollocationClientMaxReadBufferItemKey,
         &maxReadBuffer, zsDefaultCollocationClientMaxReadBuffer);
    uint32_t maxReadBufferNum = (uint32_t)atoi(maxReadBuffer.c_str());

    std::string maxWriteBuffer = "";
    loader.GetItem(zsCollocationClientMaxWriteBufferItemKey,
         &maxWriteBuffer, zsDefaultCollocationClientMaxWriteBuffer);
    uint32_t maxWriteBufferNum = (uint32_t)atoi(maxWriteBuffer.c_str());

    BalHandle<ZsCollocationClient> client(
        new ZsCollocationClient(eventLoop_, connetTimeoutNum, heartbeatNum,
            timeoutNum, maxPackageNum, maxReadBufferNum, maxWriteBufferNum)
    );

    if (client)
    {
        std::string address = "";
        loader.GetItem(zsCollocationAddressItemKey,
             &address, zsDefaultCollocationAddress);

        uint16_t port = 0; int cur = 0;
        std::string addressIp = "", addressPort = "";
        for (; cur < address.length(); ++cur)
        {
            if (':' == address[cur]) break;
            addressIp += address[cur];
        }

        cur++;
        for (; cur < address.length(); ++cur)
        {
            addressPort += address[cur];
        }
        port = (uint16_t)atoi(addressPort.c_str());

        printf("%s,  %d\n", addressIp.c_str(), port);
        BalHandle<BalInetAddress> colAddress(
            new BalInetAddress(addressIp.c_str(), port, false));
        client->Start(nodeTree, colAddress);
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
