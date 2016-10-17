#ifndef Ballet_ThreadTask_BalTaskBind_H
#define Ballet_ThreadTask_BalTaskBind_H
#include "Common/BalInct.h"
#include "BalTask.h"

namespace Ballet
{
    namespace Thread
    {
        template<class t>
        class BalTaskBind: public BalThreadTask
        {
            typedef void (t::* __pfunc) ();

        private:
            void DoTask()
            {
                if (func_)
                {
                    ((&object_)->*func_)();
                }
                ForceRelease();
            }

        public:
            static BalThreadTask* CreateTask(__pfunc func)
            {
                if (!func) return nullptr_();
                BalTaskBind<t>* task = new(std::nothrow) BalTaskBind<t>();
                if (!task) return nullptr_();
                task->func_ = func;
                return task;
            }

        private:
            t object_; __pfunc func_;
        };
    }
}
#endif
