#include "ZsCollocationClient.h"
using namespace Zeus;

ZsCollocationClient::ZsCollocationClient(BalHandle<BalEventLoop>)
{

}

bool ZsCollocationClient::Start(BalHandle<ZsNodeTree>, BalHandle<BalInetAddress>)
{
    return true;
}
