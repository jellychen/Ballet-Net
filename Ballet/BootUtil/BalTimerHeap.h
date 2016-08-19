#ifndef Ballet_BootUtil_BalTimerHeap_H
#define Ballet_BootUtil_BalTimerHeap_H
#include "Common/BalInct.h"
#include "BalTimeStamp.h"
#include "BalTimerDefine.h"

namespace Ballet
{
    namespace BootUtil
    {
        class BalTimeHeap :public BalNoCoable
        {
        public:
            BalTimeHeap();
            virtual ~BalTimeHeap();

        public:
            bool TickTimer();
            bool SetTimerOut(int id, BalTimerCallback&, uint32_t time);
            bool SetTimerLoop(int id, BalTimerCallback&, uint32_t time);
            bool RemoveTimer(int id, BalTimerCallback&);
            int64_t LastestTimeout() const;

        private:
            bool AddTimerNode(BalTimerNode& node);
            bool RemoveTimerNode(uint32_t index);
            bool SetTimerNode(int, BalTimerCallback&, uint32_t, bool);

        private:
            size_t cacheInfo_;
            BalTimeStamp timestamp_;
            mapTimerPoolT indexPool_;
            vecTimerNodePoolT heapArray_;
            listTimerInfoPoolT infoPool_;
        };
    }
}
#endif
