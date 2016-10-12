#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalHandle.h>
#include <Ballet/ServiceWorker/BalServiceManage.h>
using namespace Ballet;
using namespace ServiceWorker;

#include "ZsBrokerService.h"
using namespace Zeus;

int main(int argc, char const *argv[])
{
    printf(".........................................\n");
    printf("ZeusBroker version 1.0\n");
    printf(".........................................\n\n");

    if (argc < 2 || !argv[1])
    {
        printf("error: no input config file!\n");
        printf("usage: ZeusBroker config.ini [-d]...\n\n");
        return -1;
    }

    ZsBrokerService serviceInit(argv[1]);
    BalHandle<BalService> service(new BalService(serviceInit.callback_));
    BalHandle<BalServiceManage> manage(new BalServiceManage());
    manage->AttachService(service);
    manage->Start(argc >= 3 && 0 == strcmp("-d", argv[2]));
    return 0;
}
