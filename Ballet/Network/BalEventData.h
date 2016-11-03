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
        class BalEventLoop;
        class BalEventData: public BalNoCoable
        {
        public:
            BalEventData()
            {
                fd_ = 0; index_ = -1;
                needDelEvent_ = false;
            }

            virtual ~BalEventData()
            {
                if (needDelEvent_)
                {
                    throw std::runtime_error("BalEventData NeedDelEvent_ Panic!!");
                    abort();
                }
            }

        public:
            void Reset()
            {
                if (needDelEvent_)
                {
                    throw std::runtime_error("BalEventData Reset Panic!!");
                    abort();
                }
                callback_.Clear(); fd_ = 0; index_ = -1;
            }

        public:
            int fd_, index_;
            bool needDelEvent_;
            BalEventCallback callback_;
        };
    }
}
#endif//Ballet_Network_BalEventData_H
