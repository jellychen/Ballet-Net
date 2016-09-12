
#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalHandle.h>
#include <Ballet/Network/BalEventLoop.h>
#include <Ballet/Network/BalTcpServer.h>
using namespace Ballet;

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

using namespace Ballet::BootUtil;
using namespace Ballet::Network;

class Tprotocol: public IBalProtocol
{
public:
    virtual BalProtocolStatus CalSize(const char*, uint32_t, uint32_t*)
    {
        std::cout<<"CalSize"<<std::endl;
        return StatusNoEnough;
    }

    virtual bool Encode(const char*, uint32_t, BalHandle<BalChannel>)
    {
        return true;
    }

    virtual bool Decode(const char*, uint32_t, BalHandle<BalChannel>)
    {
        return true;
    }
};

class t_TcpServer_class
{
public:
    t_TcpServer_class():callback(this)
    {
        callback->HookOnConnect(&t_TcpServer_class::OnConnect);

        BalHandle<BalEventLoop> eventLoop(new BalEventLoop());
        eventLoop->Create();

        BalHandle<IBalProtocol> protocol(new Tprotocol());
        BalHandle<BalInetAddress> addr(new BalInetAddress(9492, false, false));
        BalHandle<BalTcpServer> server
        (
            new BalTcpServer(false, eventLoop, protocol, 10240, callback, 10000, 10000, 10000)
        );


        server->SetNoDelay(true);
        server->SetReuseAddr(true);
        server->Start(addr);

        eventLoop->DoEventLoop();
    }

    void OnConnect(BalHandle<BalTcpConnection> conn, bool success)
    {

        std::cout<<"OnConnect"<<std::endl;
    }

    CBalTcpCallbackPtr<t_TcpServer_class> callback;
};

void t_TcpServer_main()
{
    t_TcpServer_class server;
}
