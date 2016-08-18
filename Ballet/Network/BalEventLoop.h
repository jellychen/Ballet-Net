#ifndef Ballet_Network_BalEventLoop_H
#define Ballet_Network_BalEventLoop_H
#include "Common/BalInct.h"
#include "BalNetworkInct.h"
#include "BalElement.h"
#include "BalEventCallback.h"
#include <list>
#include <map>

namespace Ballet
{
    namespace Network
    {
        enum BalEventEnum
        {
            EventNone = 0, EventRead = 1, EventWrite = 2,
        };

        class BalEventLoop :public BalElement
        {
        public:
            BalEventLoop();
            virtual ~BalEventLoop();

        public:
            bool Create() throw();
            bool AddDelayReleaseElement(BalHandle<BalElement>&);
            bool SetEventListener(int, BalEventEnum, BalEventCallback&);
            bool DeleteEventListener(int id, BalEventEnum event);

        private:
            int efd_; bool created_;
            typedef std::list<BalHandle<BalElement> > vecReleaseListT;
            vecReleaseListT releaseList_;
            typedef std::map<int, BalEventCallbackWrapper> mapEventPoolT;
            mapEventPoolT eventPool_;
        };
    }
}
#endif
