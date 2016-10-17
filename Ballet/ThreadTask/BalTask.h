#ifndef Ballet_ThreadTask_BalTask_H
#define Ballet_ThreadTask_BalTask_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace Thread
    {
        class BalThreadTask
        {
        public:
            virtual ~BalThreadTask()
            {

            }

        public:
            virtual void DoTask() = 0;

        protected:
            virtual void ForceRelease()
            {
                delete this;
            }
        };
    }
}
#endif
