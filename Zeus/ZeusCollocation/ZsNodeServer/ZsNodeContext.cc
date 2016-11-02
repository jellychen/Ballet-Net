#include "ZsNodeContext.h"
using namespace Zeus;

ZsNodeContext::ZsNodeContext(BalHandle<ZsWorkboardOptions> options)
{
    if (!options)
    {
        throw std::runtime_error("ZsNodeContext Construct Failed@1");
    }

    BalHandle<BalEventLoop> eventLoop(new BalEventLoop());
    eventLoop_ = eventLoop;
    if (!eventLoop_)
    {
        throw std::runtime_error("ZsNodeContext Construct Failed@2");
    }
}

bool ZsNodeContext::StartDoEvent() const
{
    if (eventLoop_)
    {
        return eventLoop_->DoEventLoop();
    }
    return false;
}
