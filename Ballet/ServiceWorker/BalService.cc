#include "BalService.h"
using namespace Ballet;
using namespace ServiceWorker;

BalService::BalService(BalServiceCallback callback, uint32_t count)
                                :count_(count), callback_(callback)
{
    if (0 == count_ || !callback_ || !callback_->IsCallable())
    {
        throw std::runtime_error("BalService Construct Failed");
    }
}

BalService::~BalService()
{

}

void BalService::Start() const
{
    if (callback_ && callback_->IsCallable())
    {
        BalService* that = (BalService*)this;
        BalHandle<BalService> service(that, shareUserCount_);
        callback_->OnStart(service);
    }
}

void BalService::ServiceMain() const
{
    if (callback_ && callback_->IsCallable())
    {
        BalService* that = (BalService*)this;
        BalHandle<BalService> service(that, shareUserCount_);
        callback_->OnServiceMain(service);
    }
}

uint32_t BalService::Count() const
{
    return count_;
}

bool BalService::ServiceAvailable() const
{
    return callback_ && callback_->IsCallable();
}
