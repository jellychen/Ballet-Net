#ifndef Ballet_Network_BalTcpCallback_H
#define Ballet_Network_BalTcpCallback_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace Network
    {
        class BalTcpClient;
        class BalTcpConnection;

        struct IBalTcpCallback :public BalCallback
        {
            // note: call
            virtual void OnConnect(BalHandle<BalTcpConnection> conn, bool success) =0;

            // note: call when fd close
            virtual void OnClose(BalHandle<BalTcpConnection> conn, bool accord) =0;

            // note: write buffer full
            virtual void OnWriteBufferFull(BalHandle<BalTcpConnection> conn) =0;

            // note: write buffer empty
            virtual void OnWriteBufferDrain(BalHandle<BalTcpConnection> conn) =0;

            //  note: call when fd read package
            virtual void OnReceive(BalHandle<BalTcpConnection> conn, const char* buffer, uint32_t len) =0;
        };

        struct IBalTcpClientCallback :public BalCallback
        {
            // note: call
            virtual void OnConnect(BalHandle<BalTcpClient> client, bool success) =0;

            // note: call when fd close
            virtual void OnClose(BalHandle<BalTcpClient> client, bool accord) =0;

            // note: write buffer full
            virtual void OnWriteBufferFull(BalHandle<BalTcpClient> client) =0;

            // note: write buffer empty
            virtual void OnWriteBufferDrain(BalHandle<BalTcpClient> client) =0;

            //  note: call when fd read package
            virtual void OnReceive(BalHandle<BalTcpClient> client, const char* buffer, uint32_t len) =0;
        };

        BalCallbackSinkBegin(CBalTcpCallback)
        BalCallbackSink(void, OnConnect, (BalHandle<BalTcpConnection> client, bool success), (client, success))
        BalCallbackSink(void, OnClose, (BalHandle<BalTcpConnection> client, bool accord), (client, accord))
        BalCallbackSink(void, OnWriteBufferFull, (BalHandle<BalTcpConnection> client), (client))
        BalCallbackSink(void, OnWriteBufferDrain, (BalHandle<BalTcpConnection> client), (client))
        BalCallbackSink(void, OnReceive, (BalHandle<BalTcpConnection> client, const char* buffer, uint32_t len), (client, buffer, len))
        BalCallbackSinkComplete()
        BalCallbackSinkPtrDefine(CBalTcpCallback, IBalTcpCallback)

        BalCallbackSinkBegin(CBalTcpClientCallback)
        BalCallbackSink(void, OnConnect, (BalHandle<BalTcpClient> client, bool success), (client, success))
        BalCallbackSink(void, OnClose, (BalHandle<BalTcpClient> client, bool accord), (client, accord))
        BalCallbackSink(void, OnWriteBufferFull, (BalHandle<BalTcpClient> client), (client))
        BalCallbackSink(void, OnWriteBufferDrain, (BalHandle<BalTcpClient> client), (client))
        BalCallbackSink(void, OnReceive, (BalHandle<BalTcpClient> client, const char* buffer, uint32_t len), (client, buffer, len))
        BalCallbackSinkComplete()
        BalCallbackSinkPtrDefine(CBalTcpClientCallback, IBalTcpClientCallback)
    }
}
#endif
