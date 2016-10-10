#ifndef Ballet_Network_BalUdpServer_H
#define Ballet_Network_BalUdpServer_H
#include "Common/BalInct.h"
#include "BalNetworkInct.h"
#include "BalElement.h"
#include "BalUdpProtocol.h"
#include "BalUdpSocket.h"
#include "BalUdpCallback.h"
#include "BalEventLoop.h"

namespace Ballet
{
    namespace Network
    {
        class BalUdpServer
            :public BalElement, public BalUdpSocket
            ,public BalUdpChannel, public BalShareThis
        {
        public:
            BalUdpServer(bool v6, BalHandle<BalEventLoop> eventLoop,
                BalHandle<IBalUdpProtocol> protocol, uint32_t maxPackage,
                BalHandle<IBalUdpCallback> callback);
            virtual ~BalUdpServer();

        public:
            bool IsV6();
            bool Close();
            bool Start(BalHandle<BalInetAddress> addr);
            uint32_t GetMaxPackageSize() const;
            BalHandle<BalEventLoop> GetEventLoop() const;
            BalHandle<IBalUdpProtocol> GetProtocol() const;
            BalHandle<IBalUdpCallback> GetCallback() const;

        public:
            bool WriteBuffer(const char* buffer,
                    uint32_t len, BalHandle<BalInetAddress> addr);
            bool WriteRawBuffer(const char* buffer,
                    uint32_t len, BalHandle<BalInetAddress> addr);
            bool OnReceiveBuffer(const char* buffer,
                    uint32_t len, BalHandle<BalInetAddress> addr);
        protected:
            BalEventCallbackEnum ShoudRead(int id, BalHandle<BalEventLoop> el);

        private:
            uint32_t maxPackage_;
            bool detachFromEventLoop_;
            BalEventHandle eventHandle_;
            BalHandle<BalEventLoop> eventLoop_;
            BalHandle<IBalUdpCallback> callback_;
            BalHandle<IBalUdpProtocol> udpProtocol_;
            CBalEventCallbackPtr<BalUdpServer> eventCallbackPtr_;
        };
    }
}
#endif
