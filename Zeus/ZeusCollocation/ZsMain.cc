#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalHandle.h>
#include <Ballet/Network/BalEventLoop.h>
using namespace Ballet;

#include <Zeus/ZeusBase/ZsBrand.h>
#include "ZsDataStore/ZsStoreCenter.h"
#include "ZsWorkboard/ZsWorkboard.h"
#include "ZsWorkboard/ZsWorkboardOptions.h"

#include "ZeusCollocation/ZsNodeServer/ZsNodeAddEntries.h"
using namespace Zeus;

int main(int argc, char const *argv[])
{
    printf("%s\n", _g_ZsBrandStr);
    //ZsDataStoreOptions opt;
    //ZsStoreCenter center("/zs/data/", opt);
    //center.LoadDatabase("haha");
    //ZsWorkboard wb("/guodong/zs/");
    //wb.WriteProcessIdIntoFile();
    
    return 0;
}
