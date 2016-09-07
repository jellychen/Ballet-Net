#ifndef Ballet_Common_BalSignalCallback_H
#define Ballet_Common_BalSignalCallback_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace Network
    {
        class BalEventLoop;
        struct IBalSignalCallback :public BalCallback
        {
            virtual void OnReceiveSignal(int id, BalHandle<BalEventLoop> el) =0;
        };

        BalCallbackSinkBegin(CBalSignalCallback)
        BalCallbackSink(void, OnReceiveSignal, (int id, BalHandle<BalEventLoop> el), (id, el))
        BalCallbackSinkComplete()
        BalCallbackSinkPtrDefine(CBalSignalCallback, IBalSignalCallback)
    }
}
#endif
