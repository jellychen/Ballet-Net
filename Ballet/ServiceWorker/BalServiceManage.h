#ifndef Ballet_ServiceWorker_BalProcessManage_H
#define Ballet_ServiceWorker_BalProcessManage_H
#include "Common/BalInct.h"
#include "BalService.h"
#include "BalServiceSingleton.h"

namespace Ballet
{
    namespace ServiceWorker
    {
        class BalServiceManage :public BalNoCoable, public BalShareThis
        {
            typedef std::map<long, BalHandle<BalService> > servicePoolT;
        public:
            BalServiceManage();
            virtual ~BalServiceManage();

        public:
            void Start(bool deamon);
            bool AttachService(BalHandle<BalService> service);
            bool DetachService(BalHandle<BalService> service);

        public:
            bool Stop();
            bool FindServiceExit(long id, bool fork);
            bool ForkService(BalHandle<BalService> service);

        protected:
            bool exit_;
            servicePoolT servicePool_;
            servicePoolT serviceProcessPool_;
        };
    }
}
#endif
