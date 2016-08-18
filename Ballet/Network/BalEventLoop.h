#ifndef Ballet_Common_BalEventLoop_H
#define Ballet_Common_BalEventLoop_H
#include "Common/BalInct.h"
#include "BalElement.h"
#include "BalEventCallback.h"
#include <list>

namespace Ballet
{
    namespace Network
    {
        enum BalEventEnum
        {
            EventNone, EventRead, EventWrite,
        };

        class BalEventLoop :public BalElement
        {
        public:
            BalEventLoop();
            virtual ~BalEventLoop();

        public:
            bool Init() throw();
            bool AddDelayReleaseElement(BalHandle<BalElement>&);
            bool DeleteEventListener(int id, BalEventEnum event);
            bool SetEventListener(int id, BalEventEnum event, BalHandle<IBalEventCallback>&);

        private:
            int efd_;
            typedef std::list<BalHandle<BalElement> > vecReleaseListT;
            vecReleaseListT releaseList_;
        };
    }
}
#endif
