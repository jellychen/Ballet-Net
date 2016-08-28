#ifndef Ballet_ServiceWorker_BalService_H
#define Ballet_ServiceWorker_BalService_H
#include "Common/BalInct.h"
#include "BalServiceCallback.h"

namespace Ballet
{
    namespace ServiceWorker
    {
        class BalServiceManage;
        class BalService :public BalNoCoable, public BalShareThis
        {
        public:
            BalService(BalServiceCallback callback, uint32_t count = 1);
            virtual ~BalService();

        public:
            bool ServiceAvailable() const;

        private:
            void Start() const;
            void ServiceMain() const;
            uint32_t Count() const;

        protected:
            uint32_t count_;
            BalServiceCallback callback_;
            friend class BalServiceManage;
        };
    }
}
#endif
