#ifndef Ballet_BootUtil_BalMutexWatcher_H
#define Ballet_BootUtil_BalMutexWatcher_H
#include "Common/BalInct.h"
#include "BalMutex.h"

namespace Ballet
{
    namespace BootUtil
    {
        class BalMutexWatcher: public BalNoCoable
        {
        public:
            BalMutexWatcher(BalMutex* mutex)
            {
                mutex_ = mutex;

                if (mutex_)
                {
                    mutex_->Lock();
                }
            }

            ~BalMutexWatcher()
            {
                if (mutex_)
                {
                    mutex_->UnLock();
                }
            }

        private:
            BalMutex* mutex_;
        };
    }
}
#endif
