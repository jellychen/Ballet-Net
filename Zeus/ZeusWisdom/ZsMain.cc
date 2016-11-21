#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalHandle.h>
#include <Ballet/Network/BalEventLoop.h>
using namespace Ballet;

/*
#include "ZsNameData/ZsNameDefine.h"
#include "ZsNameData/ZsNameCenter.h"
*/

using namespace Zeus;

int main(int argc, char const *argv[])
{
    /*
    ZsNameCenter center("/zs/");
    std::string s = "asdasdasdasdasdasdasdasdasdads";
    for (int i = 0; i < 200000; ++i)
    {
        char buffer[20] = {0};
        sprintf(buffer, "%d", i);
        std::string key = s + buffer;
        center.AddService(key,"123123123123asdasdasdasdasdasdasdasdasdasdasd", 2);
    }
    center.DumpInfoFile("info.rdb");
    /*
    BalHandle<ZsWorkboardOptions> options(new ZsWorkboardOptions());
    options->LoadOptions("/zs/");
    BalHandle<ZsNodeContext> context(new ZsNodeContext(options));
    BalHandle<BalInetAddress> addr(new BalInetAddress("127.0.0.1", 9411, false));
    BalHandle<ZsNodeMember> member(new ZsNodeMember(context, addr));
    context->StartDoEvent();
    */
    return 0;
}
