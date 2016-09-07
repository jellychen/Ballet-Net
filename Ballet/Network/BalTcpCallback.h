#ifndef Ballet_Network_BalTcpCallback_H
#define Ballet_Network_BalTcpCallback_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace Network
    {
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

        BalCallbackSinkBegin(CBalTcpCallback)
        BalCallbackSink(void, OnConnect, (BalHandle<BalTcpConnection> conn, bool success), (conn, success))
        BalCallbackSink(void, OnClose, (BalHandle<BalTcpConnection> conn, bool accord), (conn, accord))
        BalCallbackSink(void, OnWriteBufferFull, (BalHandle<BalTcpConnection> conn), (conn))
        BalCallbackSink(void, OnWriteBufferDrain, (BalHandle<BalTcpConnection> conn), (conn))
        BalCallbackSink(void, OnReceive, (BalHandle<BalTcpConnection> conn, const char* buffer, uint32_t len), (conn, buffer, len))
        BalCallbackSinkComplete()
        BalCallbackSinkPtrDefine(CBalTcpCallback, IBalTcpCallback)
    }
}
#endif
