#ifndef Zeus_ZeusCollocation_ZsDataStore_ZsStoreCenter_H
#define Zeus_ZeusCollocation_ZsDataStore_ZsStoreCenter_H
#include <leveldb/db.h>
#include <Ballet/Common/BalInct.h>
#include <Ballet/BootUtil/BalDirUtil.h>
#include <Ballet/BootUtil/BalMutexWatcher.h>
using namespace Ballet;
using namespace BootUtil;

#include "ZsDataStoreOptions.h"

namespace Zeus
{
    class ZsStoreCenter: public BalNoCoable
    {
    public:
        ZsStoreCenter(const char*, ZsDataStoreOptions&);
        virtual ~ZsStoreCenter();

    public:


    private:
        std::string workDir_;
        ZsDataStoreOptions storeOptions_;
    };
}
#endif
