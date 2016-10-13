#ifndef Ballet_Network_BalTcpConnection_H
#define Ballet_Network_BalTcpConnection_H
#include "Common/BalInct.h"
#include "BootUtil/BalTimeStamp.h"
#include "BalNetworkInct.h"
#include "BalTcpSocket.h"
#include "BalTcpCallback.h"
#include "BalInetAddress.h"
#include "BalEventLoop.h"
#include "BalProtocol.h"
#include "BalChannel.h"
#include "BalBufferStream.h"

namespace Ballet
{
    namespace Network
    {
        enum BalConnStatusEnum
        {
            StatusNone          = 0,
            StatusConnecting    = 1,
            StatusEstablish     = 2,
            StatusClosing       = 3,
            StatusClosed        = 4,
        };

        class BalTcpServer;
        class BalTcpConnection :public BalElement,
            public BalTcpSocket, public BalChannel, public BalShareThis
        {
        public:
            BalTcpConnection(int fd, BalHandle<BalTcpServer> server);
            virtual ~BalTcpConnection();

        public:
            bool IsV6();
            bool Close(bool now);
            bool ShutdownWrite();
            bool WriteBuffer(const char* buffer, uint32_t len);
            bool WriteRawBuffer(const char* buffer, uint32_t len);
            bool BroadcastRawBuffer(const char* buffer, uint32_t len);
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
            BalWeakHandle<BalTcpServer> tcpServer_;
            CBalTimerCallbackPtr<BalTcpConnection> timerCallbackPtr_;
            CBalEventCallbackPtr<BalTcpConnection> eventCallbackPtr_;
            int32_t protocolWantSize_; int64_t lastReadTime_;
            BalBufferStream readBuffer_, writeBuffer_;
        };
    }
}
#endif
