#ifndef Ballet_BootUtil_BalTimer_H
#define Ballet_BootUtil_BalTimer_H
#include "Common/BalInct.h"
#include "BalTimerHeap.h"

namespace Ballet
{
    namespace BootUtil
    {
        class BalTimer :public BalShareThis
        {
        public:
            bool Tick();
            bool SetTimerOut(int, BalTimerCallback, uint32_t);
            bool SetTimerLoop(int, BalTimerCallback, uint32_t);
            bool RemoveTimer(int, BalTimerCallback);
            int  LastestTimeout() const;

        private:
            BalTimeHeap timerImplement_;
        };
    }
}
#endif
