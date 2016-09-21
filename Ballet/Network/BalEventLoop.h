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
            typedef std::map<int, BalHandle<BalElement> > mapHoldPoolT;
        public:
            BalEventLoop();
            virtual ~BalEventLoop();

        public:
            bool AddDelayReleaseElement(BalHandle<BalElement>&);
            bool AddHoldSomeElement(int, BalHandle<BalElement>&);
            bool RemoveHoldElement(int);
            bool SetEventListener(int id, BalEventEnum, BalEventCallback);
            bool DeleteEventListener(int id, BalEventEnum event);
            bool SetTimerOut(int, BalTimerCallback, uint32_t);
            bool SetTimerLoop(int, BalTimerCallback, uint32_t);
            bool RemoveTimer(int, BalTimerCallback);
            bool DoEventSelect(int time);
            bool DoEventLoop();
            bool DoExitEventLoop();

        protected:
            bool DoReadyPool(BalHandle<BalEventLoop> eventLoop);
            int  AddReadyItem(int, int, int, BalEventCallback&, mapEventPoolT::iterator);
            bool RemoveReadyItem(int, int, int);

        private:
            BalHandle<BalTimer> timer_;
            vecReadyPoolT readyPool_;
            mapEventPoolT eventPool_;
            vecReleaseListT releaseList_;
            mapHoldPoolT holdElementPool_;
            bool doReadyPoolProtected_;
            int efd_; bool shouldExit_;
            BalEventDataManager eventDataManager_;
        };
    }
}
#endif
