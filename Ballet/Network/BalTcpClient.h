#ifndef Ballet_Network_BalTcpClient_H
#define Ballet_Network_BalTcpClient_H
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
            BalHandle<IBalProtocol> tcpProtocol_;
            BalWeakHandle<BalEventLoop> eventLoop_;
            BalHandle<IBalTcpCallback> tcpCallback_;
            uint32_t maxPackage_, lastSendBufferTime_;
            uint32_t maxReadBufferSize_, maxWriteBufferSize_;
        };
    }
}
#endif
