#include <iostream>
using namespace std;
#include "t_Handle.h"
#include "t_BufferArray.h"
#include "t_Callback.h"
#include "t_HandleCast.h"

#include "Ballet/Network/BalEventLoop.h"

int main(int argc, char const *argv[])
{
    //t_Handle_main();
    //t_BufferArray_main();
    //t_Callback_main();
    //t_HandleCast_main();

    cout<<sizeof(Ballet::Network::BalEventCallback)<<endl;
    return 0;
}
