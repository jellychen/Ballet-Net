#ifndef Zeus_ZeusInclude_ZsDefine_H
#define Zeus_ZeusInclude_ZsDefine_H
#include <Ballet/Common/BalInct.h>
using namespace Ballet;

namespace Zeus
{
    const static char* szNoneAddress                            = "0.0.0.0:0";
    const static char* zsBrokerPortItemKey                      = "broker@port";
    const static char* zsDefaultBrokerPort                      = "6001";
    const static char* zsDefaultCollocationItemKey              = "collocation@address";
    const static char* zsDefaultCollocationAddress              = "0.0.0.0:0";

    const static char* zsCollocationClientPortItemKey           = "client@port";
    const static char* zsDefaultCollocationClientPort           = "6002";
    const static char* zsCollocationClientMaxPackageItemKey     = "client@maxpackage";
    const static char* zsDefaultCollocationClientMaxPackage     = "200000"; // 200K
    const static char* zsCollocationClientTimeoutItemKey        = "client@timeout";
    const static char* zsDefaultCollocationClientTimeout        = "30000";
    const static char* zsCollocationClientMaxReadBufferItemKey  = "client@maxreadbuffer";
    const static char* zsDefaultCollocationClientMaxReadBuffer  = "2000000";// 2MB
    const static char* zsCollocationClientMaxWriteBufferItemKey = "client@maxwritebuffer";
    const static char* zsDefaultCollocationClientMaxWriteBuffer = "2000000";// 2MB

}
#endif
