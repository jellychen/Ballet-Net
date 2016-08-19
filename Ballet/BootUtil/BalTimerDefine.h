#ifndef Ballet_BootUtil_BalTimerDefine_H
#define Ballet_BootUtil_BalTimerDefine_H
#include "Common/BalInct.h"
#include "BalTimerCallback.h"

namespace Ballet
{
    namespace BootUtil
    {
        struct BalTimerIndex
        {
            uint32_t id_; long callbackHash_;
        };

        struct BalTimerInformation
        {
            bool loop_;
            uint32_t id_, index_, timeSpec_;
            BalHandle<IBalTimerCallback> callback_;
        };

        struct BalTimerNode
        {
            BalTimerInformation* info_;
            int64_t timeout_, tickTime_;
        };

        inline bool operator< (const BalTimerIndex& l, const BalTimerIndex& r)
        {
            if (l.id_ < r.id_) return true;
            if (l.id_ > r.id_) return false;
            if (l.callbackHash_ < r.callbackHash_) return true;
            return false;
        }

        typedef std::vector<BalTimerNode> vecTimerNodePoolT;
        typedef std::list<BalTimerInformation*> listTimerInfoPoolT;
        typedef std::map<BalTimerIndex, BalTimerInformation*> mapTimerPoolT;
    }
}
#endif
