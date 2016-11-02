#include "BalCurrentThread.h"
using namespace Ballet;
using namespace BootUtil;

void BalCurrentThread::Sleep(uint64_t mtime)
{
    timespec ts = {mtime /1000, (mtime %1000) *1000000};
    ::nanosleep(&ts, &ts);
}

int BalCurrentThread::GetThreadId()
{
    static __thread int s_thread_id = 0;
    if (0 == s_thread_id)
    {
        s_thread_id = ::syscall(__NR_gettid);
    }
    return s_thread_id;
}

void BalCurrentThread::Yield()
{
    ::sched_yield();
}
