#ifndef Ballet_BootUtil_BalPerformance_H
#define Ballet_BootUtil_BalPerformance_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace BootUtil
    {
        inline long BalCurrentTime()
        {
            struct timeval val;
            ::gettimeofday(&val, NULL);
            return val.tv_sec *1000 + val.tv_usec /1000;
        }
    }
}
#endif
