
#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalHandle.h>
#include <Ballet/Network/BalEventLoop.h>
#include <Ballet/Network/BalTcpServer.h>
#include <Ballet/Network/BalNetworkInct.h>
#include <Ballet/Protocol/Arp/BalArpBroadcast.h>
#include <Ballet/Protocol/Arp/BalArpBroadcast.h>
#include <Ballet/BootUtil/BalTableOut.h>
#include <Libs/LoTrace/LoTrace.h>
using namespace Ballet;
using namespace Libs;
using namespace Logger;

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

using namespace BootUtil;
using namespace Network;
using namespace Protocol;

void t_TableouTest_main()
{
    const char* str = "\
    _____  _   _   _____   ____\n\
   |__  / | | | | | ____| / ___|\n\
     / /  | | | | |  _|   \\___ \\\n\
    / /_  | |_| | | |___   ___) |\n\
   /____|  \\___/  |_____| |____/\n\
    ";

    printf("\033[8;37m%s\033[0m", str);
    BalTableOut out(5);
    {
        std::vector<std::string> title;
        title.push_back("worker");
        title.push_back("worker");
        title.push_back("worker");
        title.push_back("worker");
        title.push_back("worker");
        out.SetTitle(title);

        for (int i = 0; i < 10; ++i)
        {
            std::vector<std::string> row;
            row.push_back("worker");
            row.push_back("123123");
            row.push_back("wrong");
            row.push_back("0");
            row.push_back("std::vector<std::string>");
            out.AddRow(row);
        }
    }
    out.DumpOut();
}
