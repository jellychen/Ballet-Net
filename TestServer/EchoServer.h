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
    virtual BalProtocolStatus CalSize(const char* buffer, uint32_t in, uint32_t* out)
    {
        if (in < sizeof(uint32_t))
            return StatusNoEnough;
        *out = *((uint32_t*)buffer);
        //printf("CalSize  %d\n", *out);
        return StatusSuccess;
    }

    virtual bool Encode(const char* buffer, uint32_t size, BalHandle<BalChannel> conn)
    {
        size += sizeof(uint32_t);
        conn->WriteRawBuffer((char*)&size, sizeof(uint32_t));
        conn->WriteRawBuffer(buffer, size - sizeof(uint32_t));
        return true;
    }

    virtual bool Decode(const char* buffer, uint32_t size, BalHandle<BalChannel> conn)
    {
        if (size > sizeof(uint32_t))
        {
            uint32_t len = *((uint32_t*)buffer);
            conn->OnReceiveBuffer(buffer + sizeof(uint32_t), len);
        }
        return true;
    }
};

class t_EchoServer_class
{
public:
    t_EchoServer_class():callback(this)
    {
        callback->HookOnConnect(&t_EchoServer_class::OnConnect);
        callback->HookOnReceive(&t_EchoServer_class::OnReceive);
        callback->HookOnClose(&t_EchoServer_class::OnClose);
        BalHandle<BalEventLoop> eventLoop(new BalEventLoop());

        BalHandle<IBalProtocol> protocol(new Tprotocol());
        BalHandle<BalInetAddress> addr(new BalInetAddress(9411, false, false));
        BalHandle<BalTcpServer> server
        (
            new BalTcpServer(false, eventLoop, protocol, 10240, callback, 2000, 10000, 10000)
        );


        server->SetNoDelay(true);
        server->SetReuseAddr(true);
        server->Start(addr);

        eventLoop->DoEventLoop();
    }

    void OnConnect(BalHandle<BalTcpConnection> conn, bool success)
    {
        conn->SetNoDelay(true);
        conn->SetReuseAddr(true);

    }

    void OnReceive(BalHandle<BalTcpConnection> conn, const char* buffer, uint32_t len)
    {
        conn->WriteBuffer(buffer, len);
        conn->Close(false);
    }

    void OnClose(BalHandle<BalTcpConnection> conn, bool accord)
    {
    }


    CBalTcpCallbackPtr<t_EchoServer_class> callback;
};

void EchoServer_main()
{
    t_EchoServer_class server;
}
