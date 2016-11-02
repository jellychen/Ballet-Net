#ifndef Ballet_BootUtil_BalMutex_H
#define Ballet_BootUtil_BalMutex_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace BootUtil
    {
        class BalMutex: public BalNoCoable
        {
        public:
            BalMutex();
            virtual ~BalMutex();

        public:
            void Lock();
            void UnLock();

        public:
            pthread_mutex_t mutex_;
        };
    }
}
#endif
