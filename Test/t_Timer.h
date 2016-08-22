
#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalHandle.h>
#include <Ballet/Network/BalEventLoop.h>
using namespace Ballet;

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

using namespace Ballet::BootUtil;
using namespace Ballet::Network;

class t_Timer_class:public BalShareThis
{
public:
    t_Timer_class():Ptr(this),eventLoop(new BalEventLoop)
    {
        std::cout << "init" << std::endl;
        Ptr->HookOnTime(&t_Timer_class::OnTime);
    }

    virtual ~t_Timer_class()
    {
        std::cout << "uninit" << std::endl;
    }

    void OnTime(uint32_t id, BalHandle<BalTimer> timer)
    {
        std::cout << "OnTime" << std::endl;
        if (timer)
        timer->SetTimerOut(0, Ptr.GetHandle(), 1000);
    }

    void timerTest()
    {
        eventLoop->Create();
        eventLoop->SetTimerOut(0, Ptr.GetHandle(), 1000);
        eventLoop->DoEventLoop();
    }
    BalHandle<BalEventLoop> eventLoop;
    CBalTimerCallbackPtr<t_Timer_class> Ptr;
};

void t_Timer_main()
{
    BalHandle<t_Timer_class> ptr(new t_Timer_class);
    ptr->timerTest();
}
