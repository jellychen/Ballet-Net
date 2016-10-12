#include "ZsBrokerService.h"
using namespace std;
using namespace Zeus;

ZsBrokerService::ZsBrokerService(const char* file):callback_(this)
{
    configFile_ = file;
    callback_->HookOnStart(&ZsBrokerService::OnStart);
    callback_->HookOnServiceMain(&ZsBrokerService::OnServiceMain);
}

void ZsBrokerService::OnStart(BalHandle<BalService>)
{

}

void ZsBrokerService::OnServiceMain(BalHandle<BalService>)
{

}
