#ifndef Ballet_Protocol_Http_BalHttpCallback_H
#define Ballet_Protocol_Http_BalHttpCallback_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace Protocol
    {
        enum BalHttpCallbackErrorEnum
        {
            HttpErrorNone       = 0,
            HttpErrorDecode     = 1,
            HttpErrorEncode     = 2,
            HttpErrorExceed     = 3,
        };

        class BalHttpConnection;
        typedef BalHandle<BalHttpConnection> BalHttpConnectionPtr;
        struct IBalHttpCallback :public BalCallback
        {
            virtual bool OnConnect(BalHttpConnectionPtr conn, bool success) =0;
            virtual bool OnHttpBegin(BalHttpConnectionPtr conn) =0;
            virtual bool OnHttpHeader(BalHttpConnectionPtr conn) =0;
            virtual bool OnHttpBody(BalHttpConnectionPtr conn, const char* buffer, uint32_t) =0;
            virtual bool OnHttpComplete(BalHttpConnectionPtr conn) =0;
            virtual bool OnHttpError(BalHttpConnectionPtr conn, BalHttpCallbackErrorEnum error) =0;
            virtual bool OnHttpClose(BalHttpConnectionPtr conn, bool accord) =0;
            virtual void OnWriteBufferFull(BalHttpConnectionPtr conn) =0;
            virtual void OnWriteBufferDrain(BalHttpConnectionPtr conn) =0;
        };

        BalCallbackSinkBegin(CBalHttpCallback)
        BalCallbackSink(void, OnConnect, (BalHttpConnectionPtr conn, bool success), (conn, success))
        BalCallbackSink(void, OnHttpBegin, (BalHttpConnectionPtr conn), (conn))
        BalCallbackSink(void, OnHttpHeader, (BalHttpConnectionPtr conn), (conn))
        BalCallbackSink(void, OnHttpBody, (BalHttpConnectionPtr conn, const char* buffer, uint32_t len), (conn, buffer, len))
        BalCallbackSink(void, OnHttpComplete, (BalHttpConnectionPtr conn), (conn))
        BalCallbackSink(void, OnHttpError, (BalHttpConnectionPtr conn, BalHttpCallbackErrorEnum error), (conn, error))
        BalCallbackSink(void, OnHttpClose, (BalHttpConnectionPtr conn, bool accord), (conn, accord))
        BalCallbackSink(void, OnWriteBufferFull, (BalHttpConnectionPtr conn), (conn))
        BalCallbackSink(void, OnWriteBufferDrain, (BalHttpConnectionPtr conn), (conn))
        BalCallbackSinkComplete()
        BalCallbackSinkPtrDefine(CBalHttpCallback, IBalHttpCallback)
    }
}
#endif//Ballet_Protocol_Http_BalHttpCallback_H
