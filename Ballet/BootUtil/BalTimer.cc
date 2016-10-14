#include "BalTimer.h"
using namespace Ballet;
using namespace BootUtil;

bool BalTimer::Tick()
{
    BalHandle<BalTimer> timerPtr(this, shareUserCount_);
    return timerImplement_.Tick(timerPtr);
}

bool BalTimer::SetTimerOut(int id, BalTimerCallback callback, uint32_t time)
{
    return timerImplement_.SetTimerOut(id, callback, time);
}

bool BalTimer::SetTimerLoop(int id, BalTimerCallback callback, uint32_t time)
{
    return timerImplement_.SetTimerLoop(id, callback, time);
}

bool BalTimer::RemoveTimer(int id, BalTimerCallback callback)
{
    return timerImplement_.RemoveTimer(id, callback);
}

int BalTimer::LastestTimeout() const
{
    return timerImplement_.LastestTimeout();
}
