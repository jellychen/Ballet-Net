#include "ZsNodeServer.h"
using namespace Zeus;

ZsNodeServer::ZsNodeServer(bool v6, BalHandle<BalEventLoop> eventLoop,
    uint32_t maxPackage, uint32_t maxReadBufferSize, uint32_t maxWriteBufferSize,
    uint32_t timeout):callback_(this)
{
    BalHandle<IBalProtocol> protocol(new ZsClientProtocol());
    BalHandle<BalTcpServer> server
    (
        new BalTcpServer(v6, eventLoop, protocol, maxPackage,
            callback_, maxReadBufferSize, maxWriteBufferSize, timeout)
    );
    server_ = server;

    if (server_)
    {
        server_->SetNoDelay(true); server_->SetReuseAddr(true);
    }
}

ZsNodeServer::~ZsNodeServer()
{

}

bool ZsNodeServer::Start(BalHandle<BalInetAddress> addr)
{
    if (server_ && addr)
    {
        return server_->Start(addr);
    }
    return false;
}

bool ZsNodeServer::OnConnect(BalHandle<BalTcpConnection> conn, bool success)
{
    if (conn)
    {
        conn->SetNoDelay(true); conn->SetReuseAddr(true);
    }
}

void ZsNodeServer::OnReceive(TConn conn, const char* buffer, uint32_t len)
{
    if (len <= sizeof(uint16_t) || !buffer || !conn) return;
    uint16_t command  = *((uint16_t*)buffer);
    if (command == (uint16_t)(ZsNcVoteRequest))
    {
        OnVoteRequest(conn, buffer + sizeof(uint16_t), len - sizeof(uint16_t));
    }
    else if (command == (uint16_t)(ZsNcAddEntriesRequest))
    {
        OnAddEntriesRequest(conn, buffer + sizeof(uint16_t), len - sizeof(uint16_t));
    }
}

void ZsNodeServer::OnVoteRequest(TConn conn, const char* buffer, uint32_t len)
{
    if (!buffer || !conn) return;
    ZsVoteRequest request;
    msgpack::unpack(buffer, len).get().convert(request);

}

void ZsNodeServer::OnAddEntriesRequest(TConn conn, const char* buffer, uint32_t len)
{
    if (!buffer || !conn) return;
    ZsAddEntriesRequest request;
    msgpack::unpack(buffer, len).get().convert(request);
}
