#ifndef Ballet_Common_BalSignalCallbackPool_H
#define Ballet_Common_BalSignalCallbackPool_H
#include "Common/BalInct.h"
#include "BalSignalCallback.h"

namespace Ballet
{
    namespace Network
    {
        class BalSignalCallbackPool
        {
            typedef std::map<int, BalHandle<IBalSignalCallback> > mapSignalCallbackPoolT;
        public:
            BalSignalCallbackPool();
            virtual ~BalSignalCallbackPool();

        public:
            void ReceiveSignal(int signal, BalHandle<BalEventLoop>);
            bool AddSignalCallback(int, BalHandle<IBalSignalCallback>);
            bool RemoveSignalCallback(int);

        private:
            mapSignalCallbackPoolT callbackPool_;
        };
    }
}
#endif
