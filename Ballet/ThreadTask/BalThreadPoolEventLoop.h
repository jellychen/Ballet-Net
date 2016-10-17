#ifndef Ballet_ThreadTask_BalThreadPoolEventLoop_H
#define Ballet_ThreadTask_BalThreadPoolEventLoop_H
#include "Common/BalInct.h"
#include "Network/BalEventLoop.h"
#include "BalTaskCommit.h"

namespace Ballet
{
    using namespace Network;

    namespace Thread
    {
        class BalThreadPoolEventLoop
            :public BalTaskCommit, public BalEventLoop
        {
            typedef std::queue<BalThreadTask*> taskQueueT;
        public:
            BalThreadPoolEventLoop(uint32_t);
            virtual ~BalThreadPoolEventLoop();

        public:
            void DoTaskInThreadPool(BalThreadTask* task);

        protected:
            void Commit(BalThreadTask* task);
            void ExecuteTaskInCurrentThread();

        protected:
            BalEventCallbackEnum OnTask(int id, BalHandle<BalEventLoop> el);

        private:
            int eventFd_;
            taskQueueT queue_[2];
            BalEventHandle event_;
            pthread_mutex_t queuelocker_;
            taskQueueT *inQueue_, *outQueue_;
            CBalEventCallbackPtr<BalThreadPoolEventLoop> callback_;
        };
    }
}
#endif
