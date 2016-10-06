#ifndef Ballet_Network_BalUdpServer_H
#define Ballet_Network_BalUdpServer_H
#include "Common/BalInct.h"
#include "BalNetworkInct.h"
#include "BalElement.h"
#include "BalProtocol.h"
#include "BalUdpSocket.h"
#include "BalUdpCallback.h"
#include "BalEventLoop.h"

namespace Ballet
{
    namespace Network
    {
        class BalUdpServer
            :public BalElement, public BalUdpSocket, public BalShareThis
        {
        public:
            BalUdpServer(bool v6, BalHandle<BalEventLoop> eventLoop,
                BalHandle<IBalProtocol> protocol, uint32_t maxPackage,
                BalHandle<IBalUdpCallback> callback);
            virtual ~BalUdpServer();

        public:
            bool IsV6();
            bool Close();
            bool Start(BalHandle<BalInetAddress> addr);
            uint32_t GetTimeout() const;
            uint32_t GetMaxPackageSize() const;
            BalHandle<BalEventLoop> GetEventLoop() const;
            BalHandle<IBalProtocol> GetProtocol() const;
            BalHandle<IBalUdpCallback> GetCallback() const;

        private:
            uint32_t maxPackage_;
            BalHandle<BalEventLoop> eventLoop_;
            BalHandle<IBalUdpCallback> callback_;
            BalHandle<IBalProtocol> udpProtocol_;
        };
    }
}
#endif
