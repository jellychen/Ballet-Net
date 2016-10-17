#ifndef Ballet_ThreadTask_BalTaskCommit_H
#define Ballet_ThreadTask_BalTaskCommit_H
#include "Common/BalInct.h"
#include "BalTask.h"

namespace Ballet
{
    namespace Thread
    {
        class BalTaskCommit
        {
        public:
            virtual void Commit(BalThreadTask*) = 0;
        };
    }
}
#endif
