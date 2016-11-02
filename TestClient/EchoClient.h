#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalHandle.h>
#include <Ballet/Network/BalEventLoop.h>
#include <Ballet/Network/BalTcpServer.h>
#include <Ballet/Network/BalTcpClient.h>
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

class t_EchoClient_class
{
public:
    int times;
    t_EchoClient_class():callback(this),times(0)
    {
        callback->HookOnConnect(&t_EchoClient_class::OnConnect);
        callback->HookOnReceive(&t_EchoClient_class::OnReceive);
        callback->HookOnClose(&t_EchoClient_class::OnClose);
        BalHandle<BalEventLoop> eventLoop(new BalEventLoop());

        BalHandle<IBalProtocol> protocol(new Tprotocol());
        BalHandle<BalInetAddress> addr(new BalInetAddress("127.0.0.1", 9411, false));
        BalHandle<BalTcpClient> client(new BalTcpClient(eventLoop,
            protocol, 10000, callback, 1000, 30000, 30000));


        client->Connect(addr, 1000);
        client->SetNoDelay(true);
        client->SetReuseAddr(true);

        eventLoop->DoEventLoop();



        printf("%s\n", "~t_EchoClient_class");
    }

    void OnConnect(BalHandle<BalTcpClient> conn, bool success)
    {
        times++;
        if (times % 1000 == 0)
        {
            printf("%d\n", times);
        }
        conn->WriteBuffer("guodong", 8);
    }

    void OnReceive(BalHandle<BalTcpClient> client, const char* buffer, uint32_t len)
    {

        //printf("%s\n", buffer);
        //client->WriteBuffer("guodong", 8);
    }

    void OnClose(BalHandle<BalTcpClient> client, bool accord)
    {
        BalHandle<BalInetAddress> addr(new BalInetAddress("127.0.0.1", 9411, false));
        client->Connect(addr, 1000);
        client->SetNoDelay(true);
        client->SetReuseAddr(true);
    }


    CBalTcpClientCallbackPtr<t_EchoClient_class> callback;
};

void EchoClient_main()
{
    signal(SIGPIPE, SIG_IGN);       // 向无读进程的管道写数据
        signal(SIGTTOU, SIG_IGN);       // 后台程序尝试写操作
        signal(SIGTTIN, SIG_IGN);

    t_EchoClient_class server;


}
