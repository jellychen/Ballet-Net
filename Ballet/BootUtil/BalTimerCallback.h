#ifndef Ballet_BootUtil_BalTimerCallback_H
#define Ballet_BootUtil_BalTimerCallback_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace BootUtil
    {
        class BalTimer;

        struct IBalTimerCallback :public BalCallback
        {
            virtual void OnTime(uint32_t, BalHandle<BalTimer>);
        };

        typedef BalHandle<IBalTimerCallback> BalTimerCallback;
        BalCallbackSinkBegin(CBalTimerCallback)
        BalCallbackSink(void, OnTime, (uint32_t id, BalHandle<BalTimer> timer), (id, timer))
        BalCallbackSinkComplete()
        BalCallbackSinkPtrDefine(CBalTimerCallback, IBalTimerCallback)
    }
}
#endif
