#ifndef Zeus_ZeusInclude_ZsDefine_H
#define Zeus_ZeusInclude_ZsDefine_H
#include <Ballet/Common/BalInct.h>
using namespace Ballet;

namespace Zeus
{
    const static char* szNoneAddress                            = "0.0.0.0:0";
    const static char* zsBrokerPortItemKey                      = "broker_port";
    const static char* zsDefaultBrokerPort                      = "6001";
    const static char* zsCollocationAddressItemKey              = "collocation_address";
    const static char* zsDefaultCollocationAddress              = "127.0.0.1:6008";
    const static char* zsCollocationClientPortItemKey           = "client_port";
    const static char* zsDefaultCollocationClientPort           = "6008";
    const static char* zsCollocationClientMaxPackageItemKey     = "client_maxpackage";
    const static char* zsDefaultCollocationClientMaxPackage     = "8000000"; // 200K
    const static char* zsCollocationClientTimeoutItemKey        = "client_timeout";
    const static char* zsDefaultCollocationClientTimeout        = "80000";
    const static char* zsCollocationClientConnectTimeoutItemKey = "client_connect_timeout";
    const static char* zsDefaultCollocationClientConnectTimeout = "5000";
    const static char* zsCollocationClientHeartbeatItemKey      = "client_heart_beat";
    const static char* zsDefaultCollocationClientHeartbeat      = "30000";
    const static char* zsCollocationClientMaxReadBufferItemKey  = "client_maxreadbuffer";
    const static char* zsDefaultCollocationClientMaxReadBuffer  = "2000000";// 2MB
    const static char* zsCollocationClientMaxWriteBufferItemKey = "client_maxwritebuffer";
    const static char* zsDefaultCollocationClientMaxWriteBuffer = "2000000";// 2MB

}
#endif
