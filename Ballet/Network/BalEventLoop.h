#ifndef Ballet_Network_BalEventLoop_H
#define Ballet_Network_BalEventLoop_H
#include "Common/BalInct.h"
#include "BootUtil/BalTimer.h"
#include "BalNetworkInct.h"
#include "BalElement.h"
#include "BalEventCallback.h"
#include <list>
#include <map>

namespace Ballet
{
    namespace Network
    {
        using namespace ::Ballet::BootUtil;

        enum BalEventEnum
        {
            EventNone = 0, EventRead = 1, EventWrite = 2,
        };

        class BalEventLoop
            :public BalElement ,public BalShareThis ,public BalNoCoable
        {
        public:
            BalEventLoop();
            virtual ~BalEventLoop();

        public:
            bool Create() throw();
            bool AddDelayReleaseElement(BalHandle<BalElement>&);
            bool SetEventListener(int, BalEventEnum, BalEventCallback&);
            bool DeleteEventListener(int id, BalEventEnum event);
            bool SetTimerOut(int, BalTimerCallback, uint32_t);
            bool SetTimerLoop(int, BalTimerCallback, uint32_t);
            bool RemoveTimer(int, BalTimerCallback);
            bool DoEventSelect(int time);
            bool DoEventLoop();
            bool DoExitEventLoop();

        private:
            BalHandle<BalTimer> timer_;
            int efd_; bool created_; bool shouldExit_;
            typedef std::list<BalHandle<BalElement> > vecReleaseListT;
            vecReleaseListT releaseList_;
            typedef std::map<int, BalEventCallbackWrapper> mapEventPoolT;
            mapEventPoolT eventPool_;
        };
    }
}
#endif
