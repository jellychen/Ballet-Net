#ifndef Zeus_ZeusBroker_ZsUdpProtocol_H
#define Zeus_ZeusBroker_ZsUdpProtocol_H
#include <Ballet/Common/BalInct.h>
#include <Ballet/Network/BalInetAddress.h>
#include <Ballet/Network/BalUdpServer.h>
using namespace Ballet;

namespace Zeus
{
    struct ZsUdpProtocol: public IBalUdpProtocol
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
}
#endif
