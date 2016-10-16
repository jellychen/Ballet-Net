#include "ZsClientServer.h"
using namespace std;
using namespace Zeus;

#include <fstream>

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
    tcpServer_ = server;
}

bool ZsClientServer::Start(BalHandle<ZsCollocationNodeData> nodeTree, BalHandle<BalInetAddress> addr)
{
    if (!nodeTree || !addr || !tcpServer_)
    {
        return false;
    }
    nodeTree_ = nodeTree;
    tcpServer_->SetNoDelay(true);
    tcpServer_->SetReuseAddr(true);
    return tcpServer_->Start(addr);
}

void ZsClientServer::OnConnect(BalHandle<BalTcpConnection> conn, bool success)
{
    printf("%s\n", "ZsClientServer::OnConnect");
    if (conn)
    {
        conn->SetNoDelay(true);
        conn->SetReuseAddr(true);
    }

    if (nodeTree_)
    {
        std::string buffer = nodeTree_->DumpNodeTreeData();
        conn->WriteBuffer(buffer.c_str(), buffer.size());
    }
}

void ZsClientServer::OnClose(BalHandle<BalTcpConnection> conn, bool accord)
{
    printf("%s\n", "ZsClientServer::OnClose");
}

void ZsClientServer::OnReceive(BalHandle<BalTcpConnection> conn, const char* buffer, uint32_t len)
{
    if (!conn || !buffer) return;

    ZsClientData receData;
    if (-1 == receData.UnSerialize((char*)buffer, len, true)
            || ZsClientDataHeartbeat == receData.type_)
    {
        const std::string& hbBuffer = heartbeat_.heartbeatBuffer_;
        conn->WriteBuffer(hbBuffer.c_str(), hbBuffer.size());
    }
}
