#include "ZsNodeContext.h"
using namespace Zeus;

ZsNodeContext::ZsNodeContext(BalHandle<ZsWorkboardOptions> options)
{
    if (!options)
    {
        throw std::runtime_error("ZsNodeContext Construct Failed@1");
    }
    options_ = options;
    
    BalHandle<BalEventLoop> eventLoop(new BalEventLoop());
    if (!eventLoop)
    {
        throw std::runtime_error("ZsNodeContext Construct Failed@2");
    }
    eventLoop_ = eventLoop;
}

bool ZsNodeContext::StartDoEvent() const
{
    if (eventLoop_)
    {
        return eventLoop_->DoEventLoop();
    }
    return false;
}
