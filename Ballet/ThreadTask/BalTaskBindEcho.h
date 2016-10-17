#ifndef Ballet_ThreadTask_BalTaskBindEcho_H
#define Ballet_ThreadTask_BalTaskBindEcho_H
#include "Common/BalInct.h"
#include "BalTaskCommit.h"

namespace Ballet
{
    namespace Thread
    {
        template<class t>
        class BalTaskBindEcho: public BalThreadTask
        {
            typedef void (t::* __pfunc) ();

        private:
            void DoTask()
            {
                if (::pthread_self() != threadId_)
                {
                    ((&object_)->*func_)(); commit_->Commit(this);
                }
                else
                {
                    ((&object_)->*funcEcho_)(); ForceRelease();
                }
            }

        public:
            static BalThreadTask* CreateTask(\
                BalTaskCommit* commit, __pfunc func, __pfunc funcEcho)
            {
                if (!func || !funcEcho || !commit) return nullptr_();
                BalTaskBind<t>* task = new(std::nothrow) BalTaskBindEcho<t>();
                if (task)
                {
                    task->commit_ = commit;
                    task->threadId_ = ::pthread_self();
                    task->func_ = func; task->funcEcho_ = funcEcho;
                }
                return task;
            }

        private:
            pthread_t threadId_;
            BalTaskCommit* commit_;
            t object_; __pfunc func_, funcEcho_;
        };
    }
}
#endif
