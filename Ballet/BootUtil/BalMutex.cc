#include "BalMutex.h"
using namespace Ballet;
using namespace BootUtil;

BalMutex::BalMutex()
{
    ::pthread_mutex_init(&mutex_, 0);
}

BalMutex::~BalMutex()
{
    ::pthread_mutex_destroy(&mutex_);
}

void BalMutex::Lock()
{
    ::pthread_mutex_lock(&mutex_);
}

void BalMutex::UnLock()
{
    ::pthread_mutex_unlock(&mutex_);
}
