#ifndef Ballet_BootUtil_BalTimerStamp_H
#define Ballet_BootUtil_BalTimerStamp_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace BootUtil
    {
        class BalTimeStamp :public BalCoable
        {
        public:
            int64_t Current() const;
        };
    }
}
#endif
