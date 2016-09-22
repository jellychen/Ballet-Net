#ifndef Ballet_Protocol_Http_BalHttpConnection_H
#define Ballet_Protocol_Http_BalHttpConnection_H
#include "Common/BalInct.h"
#include "Network/BalTcpConnection.h"

namespace Ballet
{
    using namespace Network;
    namespace Protocol
    {
        class BalHttpServer;
        class BalHttpConnection :public BalElement,
            public BalTcpSocket, public BalChannel, public BalShareThis
        {
        public:
            BalHttpConnection(int id, BalHandle<BalHttpServer> server);
            virtual ~BalHttpConnection();

        public:
            bool IsV6();
            bool Close(bool now);
            bool ShutdownWrite();
            bool WriteBuffer(const char* buffer, uint32_t len);
            bool WriteRawBuffer(const char* buffer, uint32_t len);
            uint32_t TimeoutTime() const;
            uint32_t MaxReadBufferSize() const;
            uint32_t MaxWriteBufferSize() const;
            BalConnStatusEnum GetStatus() const;
            BalHandle<BalInetAddress> GetPeer() const;
            BalHandle<BalInetAddress> GetLocal() const;

        protected:
            bool DoCloseProcedure(bool accord, bool delEvent);
            bool OnReceiveBuffer(const char* buffer, uint32_t len);
            void OnTime(uint32_t id, BalHandle<BalTimer> timer);

        public:
            virtual BalEventCallbackEnum ShouldRead(int id, BalHandle<BalEventLoop> el);
            virtual BalEventCallbackEnum ShouldWrite(int id, BalHandle<BalEventLoop> el);

        protected:
            BalConnStatusEnum status_;
            BalEventHandle eventHandle_;
            BalWeakHandle<BalHttpServer> httpServer_;
            CBalTimerCallbackPtr<BalHttpConnection> timerCallbackPtr_;
            CBalEventCallbackPtr<BalHttpConnection> eventCallbackPtr_;
            int32_t protocolWantSize_; int64_t lastReadTime_;
            BalBufferStream readBuffer_, writeBuffer_;
        };
    }
}
#endif//Ballet_Protocol_Http_BalHttpServer_H
