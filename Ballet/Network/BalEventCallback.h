#ifndef Ballet_Common_BalEventCallback_H
#define Ballet_Common_BalEventCallback_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace Network
    {
        class BalEventLoop;

        struct IBalEventCallback :public BalCallback
        {
            // note: call when fd can read
            virtual void ShouldRead(int id, BalEventLoop* el);

            // note: call when fd can write
            virtual void ShouldWrite(int id, BalEventLoop* el);
        };

        BalCallbackSinkBegin(CBalEventCallback)
        BalCallbackSink(void, ShouldRead,  (int id, BalEventLoop* el), (id, el))
        BalCallbackSink(void, ShouldWrite, (int id, BalEventLoop* el), (id, el))
        BalCallbackSinkComplete()
        BalCallbackSinkPtrDefine(CBalEventCallback, IBalEventCallback)
    }
}
#endif
