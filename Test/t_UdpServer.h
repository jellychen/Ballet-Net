
#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalHandle.h>
#include <Ballet/Network/BalEventLoop.h>
#include <Ballet/Network/BalTcpServer.h>
#include <Ballet/Network/BalUdpServer.h>
#include <Ballet/Protocol/Http/BalHttpServer.h>
using namespace Ballet;
using namespace Network;
using namespace ServiceWorker;
using namespace Protocol;

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

struct BalUdpProtocolTest: public IBalUdpProtocol
{
    bool Encode(const char* buffer, uint32_t len,
        BalHandle<BalUdpChannel> channel, BalHandle<BalInetAddress> addr)
    {
        channel->WriteRawBuffer(buffer, len, addr);
        return true;
    }

    bool Decode(const char* buffer, uint32_t len,
        BalHandle<BalUdpChannel> channel, BalHandle<BalInetAddress> addr)
    {
        channel->OnReceiveBuffer(buffer, len, addr);
        return true;
    }
};

class t_UdpServer_class
{
    std::string data;
public:
    t_UdpServer_class():callback(this)
    {
        data = "ashdkasdhkasdkajsdkjalksdjlkasjd";

        BalHandle<IBalUdpProtocol> protocol(new BalUdpProtocolTest());
        BalHandle<BalEventLoop> eventLoop(new BalEventLoop());
        BalHandle<BalInetAddress> addr(new BalInetAddress(8090, false, false));
        callback->HookOnReceive(&t_UdpServer_class::OnReceive);
        BalHandle<BalUdpServer> server
        (
            new BalUdpServer(false, eventLoop, protocol, 10240, callback)
        );

        //server->SetNoDelay(true);
        server->SetReuseAddr(true);
        server->Start(addr);
        eventLoop->DoEventLoop();
    }

    void OnReceive(BalHandle<BalUdpServer> server, const char*
            buffer, uint32_t len, BalHandle<BalInetAddress> addr)
    {
        server->WriteBuffer(buffer, len, addr);
    }

    virtual ~t_UdpServer_class()
    {

    }

    CBalUdpCallbackPtr<t_UdpServer_class> callback;
};

void t_UdpService_main()
{
    printf("%s\n", "t_UdpService_main");
    t_UdpServer_class udp;
    printf("%s\n", "t_UdpService_main _end");
}
