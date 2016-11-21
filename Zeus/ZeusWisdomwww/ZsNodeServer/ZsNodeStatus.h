#ifndef Zeus_ZeusCollocation_ZsNodeServer_ZsNodeStatus_H
#define Zeus_ZeusCollocation_ZsNodeServer_ZsNodeStatus_H
#include <Ballet/Common/BalInct.h>
using namespace Ballet;

namespace Zeus
{
    enum ZsNodeStatus
    {
        ZsNsFollower        = 0,
        ZsNsLeader          = 1,
        ZsNsCandidate       = 2,
        ZsNsOffline         = 3,
    };
}
#endif
