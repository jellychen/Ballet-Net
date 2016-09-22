#ifndef Ballet_Protocol_Http_BalHttpServer_H
#define Ballet_Protocol_Http_BalHttpServer_H
#include "Common/BalInct.h"
#include "Network/BalTcpServer.h"
#include "BalHttpCallback.h"
#include "BalHttpConnection.h"

namespace Ballet
{
    using namespace Network;
    namespace Protocol
    {
        class BalHttpServer
            :public BalElement, public BalTcpSocket, public BalShareThis
        {
            friend class BalHttpConnection;
            typedef std::map<int, BalHandle<BalHttpConnection> > mapConnPoolT;
        public:
            BalHttpServer(bool v6, BalHandle<BalEventLoop> eventLoop,
                uint32_t maxPackage, BalHandle<IBalHttpCallback> callback,
                uint32_t timeout, uint32_t maxReadBufferSize,
                uint32_t maxWriteBufferSize);

        public:
            bool IsV6();
            bool Close();
            bool Start(BalHandle<BalInetAddress> addr);
            uint32_t GetTimeout() const;
            uint32_t GetMaxPackageSize() const;
            uint32_t GetMaxReadBufferSize() const;
            uint32_t GetMaxWriteBufferSize() const;
            BalHandle<BalEventLoop> GetEventLoop() const;
            BalHandle<IBalHttpCallback> GetCallback() const;

        public:
            virtual BalEventCallbackEnum ShoudAccept(int id, BalHandle<BalEventLoop> el);

        private:
            bool EraseTcpConnection(int id);

        protected:
            uint32_t maxTimeout_;
            uint32_t maxPackageSize_;
            uint32_t maxReadBufferSize_;
            uint32_t maxWriteBufferSize_;
            BalEventHandle eventHandle_;
            mapConnPoolT mapConnPool_;
            BalWeakHandle<BalEventLoop> eventLoop_;
            BalHandle<IBalHttpCallback> httpCallback_;
            CBalEventCallbackPtr<BalHttpServer> eventCallbackPtr_;
        };
    }
}
#endif//Ballet_Protocol_Http_BalHttpServer_H
