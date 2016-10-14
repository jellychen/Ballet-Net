#include "ZsClientServer.h"
using namespace std;
using namespace Zeus;

ZsClientServer::ZsClientServer(BalHandle<BalEventLoop> loop,
    uint32_t maxPackage, uint32_t timeout,
    uint32_t maxReadBufferSize, uint32_t maxWriteBufferSize):tcpCallback_(this)
{
    tcpCallback_->HookOnConnect(&ZsClientServer::OnConnect);
    tcpCallback_->HookOnClose(&ZsClientServer::OnClose);
    tcpCallback_->HookOnReceive(&ZsClientServer::OnReceive);

    BalHandle<IBalProtocol> protocol(new ZsClientProtocol());
    BalHandle<BalTcpServer> server
    (
        new BalTcpServer(false, loop, protocol, maxPackage,
            tcpCallback_, timeout, maxReadBufferSize, maxWriteBufferSize)
    );
    server->SetNoDelay(true);
    server->SetReuseAddr(true);
    tcpServer_ = server;
}

bool ZsClientServer::Start(BalHandle<ZsNodeTree> nodeTree, BalHandle<BalInetAddress> addr)
{
    if (!nodeTree || !addr || !tcpServer_)
    {
        return false;
    }
    nodeTree_ = nodeTree;
    return tcpServer_->Start(addr);
}

void ZsClientServer::OnConnect(BalHandle<BalTcpConnection> conn, bool success)
{
    if (conn)
    {
        conn->SetNoDelay(true);
        conn->SetReuseAddr(true);
    }
    
}

void ZsClientServer::OnClose(BalHandle<BalTcpConnection> conn, bool accord)
{

}

void ZsClientServer::OnReceive(BalHandle<BalTcpConnection> conn, const char* buffer, uint32_t len)
{

}
