
#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalHandle.h>
#include <Ballet/Network/BalEventLoop.h>
#include <Ballet/Network/BalTcpServer.h>
#include <Ballet/ThreadTask/BalTaskEventLoop.h>
#include <Ballet/ThreadTask/BalTaskThreadPool.h>
#include <Ballet/ThreadTask/BalTaskBind.h>
using namespace Ballet;
using namespace Thread;

class ThreadTask
{
public:
    void a()
    {
        printf("%s %ld\n", "a", ::pthread_self());
        sleep(1);
    }
};

class ThreadTaskEcho
{
public:
    void a()
    {
        printf("%s\n", "a");
    }

    void b()
    {
        printf("%s\n", "b");
    }
};

void t_ThreadPool_main()
{
    BalHandle<BalTaskEventLoop> eventLoop(new BalTaskEventLoop());
    BalHandle<BalTaskThreadPool> threadPool(new BalTaskThreadPool(1));

    for (int i = 0; i < 10000; ++i)
    {
        threadPool->Commit(BalTaskBind<ThreadTask>::CreateTask(&ThreadTask::a));
    }

    eventLoop->DoEventLoop();
}
