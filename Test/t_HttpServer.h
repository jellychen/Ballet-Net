
#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalHandle.h>
#include <Ballet/Network/BalEventLoop.h>
#include <Ballet/Network/BalTcpServer.h>
#include <Ballet/Protocol/Http/BalHttpServer.h>
using namespace Ballet;
using namespace Network;
using namespace ServiceWorker;
using namespace Protocol;

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class t_HttpServer_class
{
    char data[10240*3];
public:
    t_HttpServer_class():callback(this)
    {
        for (int i = 0; i < 10240*3; ++i)
        {
            data[i] = 'd';
        }
        callback->HookOnConnect(&t_HttpServer_class::OnConnect);
        callback->HookOnHttpBegin(&t_HttpServer_class::OnHttpBegin);
        callback->HookOnHttpHeader(&t_HttpServer_class::OnHttpHeader);
        callback->HookOnHttpComplete(&t_HttpServer_class::OnHttpComplete);
        callback->HookOnHttpClose(&t_HttpServer_class::OnHttpClose);

        BalHandle<BalEventLoop> eventLoop(new BalEventLoop());
        BalHandle<BalInetAddress> addr(new BalInetAddress(1331, false, false));
        BalHandle<BalHttpServer> server
        (
            new BalHttpServer(false, eventLoop, 10240, callback, 5000, 10000)
        );

        bool s = server->SetNoDelay(true);
        server->SetReuseAddr(true);
        server->Start(addr);

        eventLoop->DoEventLoop();
    }

    bool OnConnect(BalHttpConnectionPtr conn, bool success)
    {
        conn->SetNoDelay(true);
        conn->SetReuseAddr(true);
        return true;
    }

    bool OnHttpBegin(BalHttpConnectionPtr conn)
    {
        return true;
    }

    bool OnHttpHeader(BalHttpConnectionPtr conn)
    {
        return true;
    }

    bool OnHttpHeaderComplete(BalHttpConnectionPtr conn)
    {
        return true;
    }

    bool OnHttpBody(BalHttpConnectionPtr conn, const char* buffer, uint32_t)
    {
        return true;
    }

    bool OnHttpChunkBuffer(BalHttpConnectionPtr conn, const char* buffer, uint32_t)
    {
        return true;
    }

    bool OnHttpComplete(BalHttpConnectionPtr conn, const char* buffer, uint32_t)
    {
        //std::string url;
        //conn->GetHttpUrl(&url);
        //printf(">>>  %s\n", url.c_str());

        conn->RespondBegin();
        conn->RespondVersion(1, 0);
        conn->RespondStatus(200, "ok");
        conn->RespondContentLength(10240*3);
        //conn->RespondKeepAlive();
        conn->RespondHeader("Server", "Ballet");
        conn->RespondHeaderComplete(false);
        conn->RespondBody(data, 10240*3);
        conn->RespondComplete(false);
        return true;
    }

    bool OnHttpError(BalHttpConnectionPtr conn, BalHttpCallbackErrorEnum error)
    {
        return true;
    }

    bool OnHttpClose(BalHttpConnectionPtr conn, bool accord)
    {
        return true;
    }

    void OnWriteBufferFull(BalHttpConnectionPtr conn)
    {

    }

    void OnWriteBufferDrain(BalHttpConnectionPtr conn)
    {

    }

    virtual ~t_HttpServer_class()
    {

    }

    CBalHttpCallbackPtr<t_HttpServer_class> callback;
};

void t_HttpService_main()
{
    printf("%s\n", "t_HttpService_main start");
    t_HttpServer_class server;
    printf("%s\n", "t_HttpService_main end");
}
