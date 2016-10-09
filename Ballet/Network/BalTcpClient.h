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
        class BalTcpClient :public BalElement,
            public BalTcpSocket, public BalChannel, public BalShareThis
        {
        public:
            BalTcpClient(bool v6, BalHandle<BalEventLoop> eventLoop,
                BalHandle<IBalProtocol> protocol, uint32_t maxPackage,
                BalHandle<IBalTcpCallback> callback,
                uint32_t maxReadBufferSize, uint32_t maxWriteBufferSize);

        public:
            bool IsV6();
            bool Connect(BalHandle<BalInetAddress> addr, int timeout);
            bool Close(bool now);
            bool ShutdownWrite();
            bool WriteBuffer(const char* buffer, uint32_t len);
            bool WriteRawBuffer(const char* buffer, uint32_t len);
            bool Connect(BalHandle<BalInetAddress> addr) throw();
            bool BindAddress(BalHandle<BalInetAddress> addr) throw();
            uint32_t GetMaxPackageSize() const;
            uint32_t GetMaxReadBufferSize() const;
            uint32_t GetMaxWriteBufferSize() const;
            uint32_t GetLastSendBufferTime() const;
            BalHandle<BalEventLoop> GetEventLoop() const;
            BalHandle<IBalProtocol> GetProtocol() const;
            BalHandle<IBalTcpCallback> GetCallback() const;

        protected:
            virtual BalEventCallbackEnum ShouldRead(int id, BalHandle<BalEventLoop> el);
            virtual BalEventCallbackEnum ShouldWrite(int id, BalHandle<BalEventLoop> el);

        protected:
            bool setDelayRelease_;
            BalConnStatusEnum status_;
            BalEventHandle eventHandle_;
            BalHandle<IBalProtocol> tcpProtocol_;
            BalWeakHandle<BalEventLoop> eventLoop_;
            BalHandle<IBalTcpCallback> tcpCallback_;
            uint32_t maxPackage_, lastSendBufferTime_;
            uint32_t maxReadBufferSize_, maxWriteBufferSize_;
            CBalEventCallbackPtr<BalTcpClient> eventCallbackPtr_;
        };
    }
}
#endif
