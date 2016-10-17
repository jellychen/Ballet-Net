#include <iostream>
using namespace std;
#include "t_Handle.h"
//#include "t_BufferArray.h"


#include "t_Callback.h"
#include "t_HandleCast.h"
#include "t_ShareThis.h"
#include "t_Timer.h"
#include "t_Singleton.h"
#include "t_Service.h"
#include "t_TcpServer.h"
#include "t_HttpServer.h"
#include "t_UdpServer.h"
#include "t_SerializeTest.h"

#include "t_ThreadTest.h"
#include "t_ThreadPool.h"

#include "t_ArpTest.h"
#include "Ballet/Network/BalInetAddress.h"
#include "Ballet/Network/BalEventLoop.h"
#include "Ballet/Network/BalSocket.h"

#include "t_IniLoader.h"

using namespace Ballet::Network;

int main(int argc, char const *argv[])
{

    //t_Handle_main();
    //t_Callback_main();
    //t_BufferArray_main();
    //t_Callback_main();
    //t_HandleCast_main();

    //cout<<sizeof(Ballet::Network::BalEventCallback)<<endl;
    //t_ShareThis_main();
    //t_Timer_main();
    //t_Callback_main();
    //t_Singleton_main();
    //t_Service_main();
    //t_TcpServer_main();
    //t_Arp_main();
    //t_HttpService_main();

    //t_UdpService_main();
    //t_IniLoaderTest_main();
    //t_SerializeTest_main();
    //t_ThreadTest_main();

    t_ThreadPool_main();

    return 0;
}
