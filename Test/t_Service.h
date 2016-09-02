#include <Ballet/Common/BalInct.h>
#include <Ballet/ServiceWorker/BalServiceManage.h>
using namespace Ballet;
using namespace Network;
using namespace ServiceWorker;

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class t_Service_class
{
public:
    t_Service_class():ptr(this)
    {
        ptr->HookOnStart(&t_Service_class::OnStart);
        ptr->HookOnServiceMain(&t_Service_class::OnServiceMain);
    }

    virtual ~t_Service_class()
    {

    }

    void OnStart(BalHandle<BalService>)
    {
        //std::cout << "/* message */ OnStart" << std::endl;
    }

    void OnServiceMain(BalHandle<BalService>)
    {
        //std::cout << "/* message */ OnServiceMain" << std::endl;
    }

    CBalServiceCallbackPtr<t_Service_class> ptr;
};


void t_Service_main()
{
    std::cout << BALSINGLETON_EXIT << std::endl;


    t_Service_class service_callback;
    BalHandle<IBalServiceCallback> callback; callback = service_callback.ptr.GetHandle();

    BalHandle<BalService> service(new BalService(callback, 4));
    BalHandle<BalService> service1; service1->ServiceAvailable();
    BalHandle<BalServiceManage> manage(new BalServiceManage());
    manage->AttachService(service);
    manage->Start(true);
}
