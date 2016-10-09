#ifndef Ballet_Network_BalEventLoop_H
#define Ballet_Network_BalEventLoop_H
#include "Common/BalInct.h"
#include "BootUtil/BalTimer.h"
#include "BalNetworkInct.h"
#include "BalEventHandle.h"
#include "BalEventData.h"
#include "BalElement.h"
#include "BalEventCallback.h"

namespace Ballet
{
    namespace Network
    {
        using namespace ::Ballet::BootUtil;
        class BalEventLoop
            :public BalElement ,public BalShareThis ,public BalNoCoable
        {
            typedef std::map<long, BalHandle<BalElement> > mapHoldPoolT;
        public:
            BalEventLoop();
            virtual ~BalEventLoop();

        public:
            bool AddDelayReleaseElement(BalHandle<BalElement>&);
            bool AddHoldSomeElement(long, BalHandle<BalElement>&);
            bool RemoveHoldElement(long);
            bool SetEventListener(BalEventHandle&, BalEventEnum, BalEventCallback);
            bool DeleteEventListener(BalEventHandle&, BalEventEnum event);
            bool SetTimerOut(int, BalTimerCallback, uint32_t);
            bool SetTimerLoop(int, BalTimerCallback, uint32_t);
            bool RemoveTimer(int, BalTimerCallback);
            bool DoEventSelect(int time);
            bool DoEventLoop();
            bool DoExitEventLoop();

        protected:
            bool DoReadyPool(BalHandle<BalEventLoop> eventLoop);
            int  AddReadyItem(int index, int fd,
                    BalEventEnum ready, BalEventCallback& callback, BalEventData* data);
            bool RemoveReadyItem(int index, int fd, BalEventEnum ready);

        private:
            BalHandle<BalTimer> timer_;
            vecReadyPoolT readyPool_;
            vecReleaseListT releaseList_;
            mapHoldPoolT holdElementPool_;
            bool doReadyPoolProtected_;
            int efd_; bool shouldExit_;
            BalEventDataManager eventDataManager_;
        };
    }
}
#endif
