#ifndef Ballet_Network_BalEventHandle_H
#define Ballet_Network_BalEventHandle_H
#include "Common/BalInct.h"
#include "BalEventData.h"

namespace Ballet
{
    namespace Network
    {
        enum BalEventEnum
        {
            EventNone = 0, EventRead = 1, EventWrite = 2, EventReadWrite =3,
        };

        class BalEventHandle
        {
        public:
            explicit BalEventHandle(int fd);

        public:
            int GetFd() const;
            bool IsWaitEvent() const;
            void SetEventWaitStatus(BalEventEnum event);
            BalEventEnum GetEventWaitStatus() const;

        public:
            BalEventData* eventData_;

        private:
            int fd_; BalEventEnum eventStatus_;
        };
    }
}
#endif//Ballet_Network_BalEventHandle_H
