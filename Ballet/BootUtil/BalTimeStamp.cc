#include <sys/time.h>
#include "BalTimeStamp.h"
using namespace Ballet::BootUtil;

int64_t BalTimeStamp::Current() const
{
    struct timeval tv;
    ::gettimeofday(&tv, 0);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}
