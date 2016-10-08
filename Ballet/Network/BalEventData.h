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
        struct BalEventData
        {
            int fd_;
            int index_;
            BalEventCallback callback_;
        };

        class BalEventDataManager
        {
        public:
            BalEventDataManager(uint32_t size);
            virtual ~BalEventDataManager();

        public:
            BalEventData* GetOne();
            void RevertBack(BalEventData* data);

        private:
            uint32_t maxSize_;
            typedef std::list<BalEventData*> listPoolT;
            listPoolT listPool_;
        };
    }
}
#endif//Ballet_Network_BalEventData_H
