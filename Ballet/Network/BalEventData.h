#ifndef Ballet_Network_BalEventData_H
#define Ballet_Network_BalEventData_H
#include "Common/BalInct.h"
#include "BalNetDefine.h"
#include "BalElement.h"
#include "BalEventCallback.h"

namespace Ballet
{
    namespace Network
    {
        class BalEventData
        {
        public:
            BalEventData()
            {
                fd_ = 0; index_ = -1;
            }

        public:
            int fd_;
            int index_;
            BalEventCallback callback_;
        };
    }
}
#endif//Ballet_Network_BalEventData_H
