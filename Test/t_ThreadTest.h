
#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalHandle.h>
#include <Ballet/Network/BalEventLoop.h>
#include <Ballet/Network/BalTcpServer.h>
#include <Ballet/ThreadTask/BalTaskBind.h>
using namespace Ballet;
using namespace Thread;

class ThreadTestClass
{
public:
    void __get()
    {
        printf("%s\n", "ThreadTestClass __get");
    }
};

void t_ThreadTest_main()
{
    BalThreadTask* task = BalTaskBind\
        <ThreadTestClass>::CreateTask(&ThreadTestClass::__get);
    task->DoTask();
}
