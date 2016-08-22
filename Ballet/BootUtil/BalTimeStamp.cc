#include <sys/time.h>
#include "BalTimeStamp.h"
using namespace Ballet::BootUtil;

int64_t BalTimeStamp::Current() const
{
    struct timeval tv; ::gettimeofday(&tv, 0);
    return (int64_t)tv.tv_sec * 1000 + tv.tv_usec/1000;
}
