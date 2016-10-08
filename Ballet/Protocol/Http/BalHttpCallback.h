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
            HttpErrorExceed     = 1,
            HttpErrorParser     = 2,
        };

        class BalHttpConnection;
        typedef BalHandle<BalHttpConnection> BalHttpConnectionPtr;
        struct IBalHttpCallback :public BalCallback
        {
            virtual bool OnConnect(BalHttpConnectionPtr conn, bool success) =0;
            virtual bool OnHttpBegin(BalHttpConnectionPtr conn) =0;
            virtual bool OnHttpHeader(BalHttpConnectionPtr conn) =0;
            virtual bool OnHttpHeaderComplete(BalHttpConnectionPtr conn) =0;
            virtual bool OnHttpBody(BalHttpConnectionPtr conn, const char* buffer, uint32_t) =0;
            virtual bool OnHttpChunkBuffer(BalHttpConnectionPtr conn, const char* buffer, uint32_t) =0;
            virtual bool OnHttpComplete(BalHttpConnectionPtr conn, const char* buffer, uint32_t) =0;
            virtual bool OnHttpError(BalHttpConnectionPtr conn, BalHttpCallbackErrorEnum error) =0;
            virtual bool OnHttpClose(BalHttpConnectionPtr conn, bool accord) =0;
            virtual void OnWriteBufferFull(BalHttpConnectionPtr conn) =0;
            virtual void OnWriteBufferDrain(BalHttpConnectionPtr conn) =0;
        };

        BalCallbackSinkBegin(CBalHttpCallback)
        BalCallbackSink(bool, OnConnect, (BalHttpConnectionPtr conn, bool success), (conn, success))
        BalCallbackSink(bool, OnHttpBegin, (BalHttpConnectionPtr conn), (conn))
        BalCallbackSink(bool, OnHttpHeader, (BalHttpConnectionPtr conn), (conn))
        BalCallbackSink(bool, OnHttpHeaderComplete, (BalHttpConnectionPtr conn), (conn))
        BalCallbackSink(bool, OnHttpBody, (BalHttpConnectionPtr conn, const char* buffer, uint32_t len), (conn, buffer, len))
        BalCallbackSink(bool, OnHttpChunkBuffer, (BalHttpConnectionPtr conn, const char* buffer, uint32_t len), (conn, buffer, len))
        BalCallbackSink(bool, OnHttpComplete, (BalHttpConnectionPtr conn, const char* buffer, uint32_t len), (conn, buffer, len))
        BalCallbackSink(bool, OnHttpError, (BalHttpConnectionPtr conn, BalHttpCallbackErrorEnum error), (conn, error))
        BalCallbackSink(bool, OnHttpClose, (BalHttpConnectionPtr conn, bool accord), (conn, accord))
        BalCallbackSink(void, OnWriteBufferFull, (BalHttpConnectionPtr conn), (conn))
        BalCallbackSink(void, OnWriteBufferDrain, (BalHttpConnectionPtr conn), (conn))
        BalCallbackSinkComplete()
        BalCallbackSinkPtrDefine(CBalHttpCallback, IBalHttpCallback)
    }
}
#endif//Ballet_Protocol_Http_BalHttpCallback_H
