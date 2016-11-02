#include <iostream>
using namespace std;

#include "Ballet/Network/BalInetAddress.h"
#include "Ballet/Network/BalEventLoop.h"
#include "Ballet/Network/BalSocket.h"
using namespace Ballet;
using namespace Network;

#include "EchoClient.h"

int main()
{
    EchoClient_main();
    return 0;
}
