#include <iostream>
using namespace std;
#include "t_Handle.h"
#include "t_BufferArray.h"
#include "t_Callback.h"
#include "t_HandleCast.h"
#include "t_ShareThis.h"
#include "t_Timer.h"
#include "Ballet/Network/BalInetAddress.h"
#include "Ballet/Network/BalEventLoop.h"
#include "Ballet/Network/BalSocket.h"
using namespace Ballet::Network;

int main(int argc, char const *argv[])
{
    //t_Handle_main();
    //t_BufferArray_main();
    //t_Callback_main();
    //t_HandleCast_main();

    //cout<<sizeof(Ballet::Network::BalEventCallback)<<endl;
    //t_ShareThis_main();
    t_Timer_main();
    return 0;
}
