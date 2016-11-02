#ifndef Ballet_Network_BalTcpClient_H
#define Ballet_Network_BalTcpClient_H
#include "Common/BalInct.h"
#include "BootUtil/BalTimeStamp.h"
#include "BalNetworkInct.h"
#include "BalTcpConnection.h"

namespace Ballet
{
    namespace Network
    {
        class BalTcpClient :public BalElement, public BalChannel, public BalShareThis
        {
            friend class BalSocket;
            friend class BalTcpSocket;
        public:
            BalTcpClient(BalHandle<BalEventLoop> eventLoop,
                BalHandle<IBalProtocol> protocol, uint32_t maxPackage,
                BalHandle<IBalTcpClientCallback> callback, uint32_t timeout,
                uint32_t maxReadBufferSize, uint32_t maxWriteBufferSize);
            virtual ~BalTcpClient();
            
        public:
            bool IsV6();
            bool Close(bool now);
            bool ShutdownWrite();
            bool SetNoDelay(bool set);
            bool SetReuseAddr(bool set);
            bool WriteBuffer(const char* buffer, uint32_t len);
            bool WriteRawBuffer(const char* buffer, uint32_t len);
            bool BroadcastRawBuffer(const char* buffer, uint32_t len);
            bool Connect(BalHandle<BalInetAddress> addr, int timeout);
            bool Connect(BalHandle<BalInetAddress> addr,
                BalHandle<BalInetAddress> bindAddr, int timeout);
            uint32_t GetMaxPackageSize() const;
            uint32_t GetMaxReadBufferSize() const;
            uint32_t GetMaxWriteBufferSize() const;
            BalHandle<BalEventLoop> GetEventLoop() const;
            BalHandle<IBalProtocol> GetProtocol() const;
            BalHandle<IBalTcpClientCallback> GetCallback() const;

        protected:
            bool DoCloseProcedure(bool accord, bool delEvent);
            bool OnReceiveBuffer(const char* buffer, uint32_t len);
            void OnTime(uint32_t id, BalHandle<BalTimer> timer);

        protected:
            virtual BalEventCallbackEnum ShouldRead(int id, BalHandle<BalEventLoop> el);
            virtual BalEventCallbackEnum ShouldWrite(int id, BalHandle<BalEventLoop> el);

        protected:
            BalTcpSocket socket_;
            BalConnStatusEnum status_;
            BalEventHandle eventHandle_;
            BalHandle<IBalProtocol> tcpProtocol_;
            BalWeakHandle<BalEventLoop> eventLoop_;
            BalHandle<IBalTcpClientCallback> tcpCallback_;
            int32_t protocolWantSize_;
            uint32_t maxPackage_, lastReadTime_, maxTimeout_;
            uint32_t maxReadBufferSize_, maxWriteBufferSize_;
            BalBufferStream readBuffer_, writeBuffer_;
            CBalTimerCallbackPtr<BalTcpClient> timerCallbackPtr_;
            CBalEventCallbackPtr<BalTcpClient> eventCallbackPtr_;

        };
    }
}
#endif
