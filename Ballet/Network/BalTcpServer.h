#ifndef Ballet_Network_BalTcpServer_H
#define Ballet_Network_BalTcpServer_H
#include "Common/BalInct.h"
#include "BalNetworkInct.h"
#include "BalTcpSocket.h"
#include "BalEventLoop.h"
#include "BalTcpProtocol.h"
#include "BalTcpConnection.h"
#include "BalTcpCallback.h"

namespace Ballet
{
    namespace Network
    {
        class BalTcpServer
            :public BalElement, public BalTcpSocket, public BalShareThis
        {
            friend class BalTcpConnection;
            typedef std::map<int, BalHandle<BalTcpConnection> > mapConnPoolT;
        public:
            BalTcpServer(bool v6, BalHandle<BalEventLoop> eventLoop,
                BalHandle<IBalTcpProtocol> protocol, uint32_t maxPackage,
                BalHandle<IBalTcpCallback> callback, uint32_t timeout,
                uint32_t maxReadBufferSize, uint32_t maxWriteBufferSize);

        public:
            bool IsV6();
            bool Close();
            uint32_t GetTimeout() const;
            uint32_t GetMaxPackageSize() const;
            uint32_t GetMaxReadBufferSize() const;
            uint32_t GetMaxWriteBufferSize() const;
            BalHandle<IBalTcpProtocol> GetProtocol() const;
            
        public:
            virtual BalEventCallbackEnum ShoudAccept(int id, BalHandle<BalEventLoop> el);

        private:
            bool EraseTcpConnection(int id);

        protected:
            uint32_t maxTimeout_;
            uint32_t maxPackageSize_;
            uint32_t maxReadBufferSize_;
            uint32_t maxWriteBufferSize_;
            mapConnPoolT mapConnPool_;
            BalWeakHandle<BalEventLoop> eventLoop_;
            BalHandle<IBalTcpProtocol> protocol_;
            BalHandle<IBalTcpCallback> tcpCallback_;
            CBalEventCallbackPtr<BalTcpServer> eventCallbackPtr_;
        };
    }
}
#endif
