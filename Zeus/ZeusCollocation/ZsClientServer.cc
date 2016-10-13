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

    msgpack_sbuffer sbuf;
    msgpack_sbuffer_init(&sbuf);

    /* serialize values into the buffer using msgpack_sbuffer_write callback function. */
    msgpack_packer pk;
    msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

    msgpack_pack_array(&pk, 3);
    msgpack_pack_int(&pk, 1);
    msgpack_pack_true(&pk);
    msgpack_pack_str(&pk, 7);
    msgpack_pack_str_body(&pk, "example", 7);

    /* deserialize the buffer into msgpack_object instance. */
    /* deserialized object is valid during the msgpack_zone instance alive. */
    msgpack_zone mempool;
    msgpack_zone_init(&mempool, 2048);

    msgpack_object deserialized;
    msgpack_unpack(sbuf.data, sbuf.size, NULL, &mempool, &deserialized);

    /* print the deserialized object. */
    msgpack_object_print(stdout, deserialized);
    puts("");

    msgpack_zone_destroy(&mempool);
    msgpack_sbuffer_destroy(&sbuf);

}

void ZsClientServer::OnClose(BalHandle<BalTcpConnection> conn, bool accord)
{

}

void ZsClientServer::OnReceive(BalHandle<BalTcpConnection> conn, const char* buffer, uint32_t len)
{

}
