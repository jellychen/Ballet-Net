#ifndef Ballet_BootUtil_BalCurrentThread_H
#define Ballet_BootUtil_BalCurrentThread_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace BootUtil
    {
        class BalCurrentThread
        {
        public:
            static void Sleep(uint64_t mtime);

            static int GetThreadId();
            
            static void Yield();
        };
    }
}
#endif
