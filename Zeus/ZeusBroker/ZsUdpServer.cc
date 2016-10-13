#include "ZsUdpServer.h"
using namespace Zeus;

ZsUdpServer::ZsUdpServer(BalHandle<BalEventLoop> loop):callback_(this)
{
    callback_->HookOnReceive(&ZsUdpServer::OnReceive);
    BalHandle<IBalUdpProtocol> protocol(new ZsUdpProtocol());
    BalHandle<BalUdpServer> server
    (
        new BalUdpServer(false, loop, protocol, 1024, callback_)
    );
    server_ = server;
    server_->SetReuseAddr(true);
}

bool ZsUdpServer::Start(BalHandle<ZsNodeTree> nodeTree, BalHandle<BalInetAddress> addr)
{
    if (!nodeTree || !addr || !server_) return false;
    nodeTree_ = nodeTree; server_->Start(addr);
    return true;
}

void ZsUdpServer::OnReceive(BalHandle<BalUdpServer>,
        const char* buffer, uint32_t len, BalHandle<BalInetAddress> addr)
{
    if (!server_ || !addr) return;
    if (!buffer || 0 == len || !nodeTree_)
    {
        server_->WriteRawBuffer("false", 5, addr);
    }
    else
    {
        uint32_t cur = 0;
        for (; cur < len; ++cur)
        {
            if (' ' != buffer[cur]) break;
        }

        std::string op = "";
        for (; cur < len; ++cur)
        {
            char bit = buffer[cur];
            if ('|' == bit || ' ' == bit) break;
            op += bit;
        }

        for (; cur < len; ++cur)
        {
            char bit = buffer[cur];
            if ('|' != bit && ' ' != bit) break;
        }

        std::string name = "";
        for (; cur < len; ++cur)
        {
            char bit = buffer[cur];
            if ('|' == bit || ' ' == bit) break;
            name += bit;
        }

        if ("get" == op)
        {
            std::string data = nodeTree_->RandomSelect(name);
            server_->WriteRawBuffer(data.c_str(), (uint32_t)data.length(), addr);
        }
        else if ("echo" == op)
        {
            server_->WriteRawBuffer(name.c_str(), (uint32_t)name.length(), addr);
        }
        else
        {
            server_->WriteRawBuffer("false", 5, addr);
        }
    }
}
