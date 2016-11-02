#include "ZsNodeInfoData.h"
using namespace Zeus;

ZsNodeInfoData::ZsNodeInfoData(BalHandle<ZsNodeContext> context)
{
    context_ = context;
    status_ = ZsNsFollower;
    currentTerm_ = commitIndex_ = lastApplied_ = 0;
    if (!context)
    {
        throw std::runtime_error("ZsNodeInfoData Construct Failed@1");
    }
}

ZsNodeInfoData::~ZsNodeInfoData()
{

}
