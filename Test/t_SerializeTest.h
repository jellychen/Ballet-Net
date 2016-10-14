
#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalHandle.h>
#include <Ballet/BootUtil/BalSerialize.h>
#include <Ballet/Network/BalEventLoop.h>
#include <Ballet/Network/BalTcpServer.h>
#include <Ballet/Protocol/Http/BalHttpServer.h>
using namespace Ballet;
using namespace Network;
using namespace ServiceWorker;
using namespace Protocol;

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

void t_SerializeTest_main()
{
    std::string str = "";
    BalPackInt8 data;
    data = 10;

    data.Serialize(str, false);

    BalPackInt8 data_;
    data_.UnSerialize((char*)str.c_str(), str.size(), false);
    printf("%d\n", data.rawData_);
}
