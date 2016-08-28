#ifndef Ballet_Network_BalTcpConnection_H
#define Ballet_Network_BalTcpConnection_H
#include "Common/BalInct.h"
#include "BalNetworkInct.h"
#include "BalTcpSocket.h"
#include "BalEventLoop.h"

namespace Ballet
{
    namespace Network
    {
        enum BalConnStatusEnum
        {
            StatusNone = 0,
            StatusConnecting = 1,
            StatusEstablish = 2,
            StatusClosing = 3,
            StatusClosed = 4,
        };

        class BalTcpServer;
        class BalTcpConnection
            :public BalElement, public BalTcpSocket, public BalShareThis
        {
        public:
            BalTcpConnection(int id,
                BalHandle<BalTcpServer> server,
                BalHandle<BalEventLoop> eventLoop,
                uint32_t maxReadBufferSize, uint32_t maxWriteBufferSize);
        public:
            bool IsV6();
            bool Close(bool now);
            bool ShutdownWrite();
            bool WriteBuffer(const char* buffer, uint32_t len);
            bool WriteRawBuffer(const char* buffer, uint32_t len);
            uint32_t MaxReadBufferSize() const;
            uint32_t MaxWriteBufferSize() const;
            BalConnStatusEnum GetStatus() const;
            BalHandle<BalInetAddress> GetPeer() const;
            BalHandle<BalInetAddress> GetLocal() const;

        public:
            virtual BalEventCallbackEnum ShouldRead(int id, BalHandle<BalEventLoop> el);
            virtual BalEventCallbackEnum ShouldWrite(int id, BalHandle<BalEventLoop> el);

        protected:
            uint32_t maxReadBufferSize_;
            uint32_t maxWriteBufferSize_;
            BalConnStatusEnum status_;
            BalWeakHandle<BalEventLoop> eventLoop_;
            CBalEventCallbackPtr<BalTcpConnection> eventCallbackPtr_;
        };
    }
}
#endif
