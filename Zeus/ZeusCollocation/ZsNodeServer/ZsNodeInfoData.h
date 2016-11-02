#ifndef Zeus_ZeusCollocation_ZsNodeServer_ZsNodeInfoData_H
#define Zeus_ZeusCollocation_ZsNodeServer_ZsNodeInfoData_H
#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalHandle.h>
using namespace Ballet;

#include "ZsNodeStatus.h"
#include "ZsNodeContext.h"

namespace Zeus
{
    class ZsNodeInfoData: public BalNoCoable
    {
    public:
        ZsNodeInfoData(BalHandle<ZsNodeContext> context);
        virtual ~ZsNodeInfoData();

    public:
        std::string voteFor_;
        ZsNodeStatus status_;
        uint64_t currentTerm_;
        uint64_t commitIndex_;
        uint64_t lastApplied_;

    private:
        BalHandle<ZsNodeContext> context_;
    };
}
#endif
