#ifndef Ballet_Common_BalShareThis_H
#define Ballet_Common_BalOwnerShip_H
#include "BalInct.h"
#include "BalUseCount.h"

namespace Ballet
{
    class BalShareThis
    {
    public:
        BalShareThis():shareUserCount_(0)
        {
        }

    public:
        void __InternalUseCount(BalUseCount* count)
        {
            shareUserCount_ = count;
        }

    protected:
        BalUseCount* shareUserCount_;
    };
}
#endif
