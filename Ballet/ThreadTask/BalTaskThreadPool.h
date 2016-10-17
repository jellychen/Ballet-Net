#ifndef Ballet_ThreadTask_BalTaskThreadPool_H
#define Ballet_ThreadTask_BalTaskThreadPool_H
#include "Common/BalInct.h"
#include "BalTaskCommit.h"

namespace Ballet
{
    namespace Thread
    {
        class BalTaskThreadPool :public BalTaskCommit
        {
            typedef std::queue<BalThreadTask*> taskQueueT;
        public:
            BalTaskThreadPool(uint32_t);
            virtual ~BalTaskThreadPool();

        public:
            void Commit(BalThreadTask* task);

        private:
            static void* thread_function(void*);

        private:
            struct taskThreadInfoT
            {
                bool exit_;
                taskQueueT queue_;
                pthread_cond_t threadCond_;
                pthread_mutex_t queuelocker_;
            };
            taskThreadInfoT taskThreadInfo_;
            std::vector<pthread_t> threadObjects_;
        };
    }
}
#endif
