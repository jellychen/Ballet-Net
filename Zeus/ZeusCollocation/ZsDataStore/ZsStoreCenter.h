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
        typedef BalHandle<leveldb::DB> dbHandleT;
        typedef std::map<std::string, dbHandleT> dbPoolT;

    public:
        ZsStoreCenter(const char*, ZsDataStoreOptions&);
        virtual ~ZsStoreCenter();

    public:
        bool LoadDatabase(const char* database);
        bool CloseDatabase(const char* database);

    private:
        dbPoolT dbPool_;
        BalMutex mutex_;
        std::string workDir_;
        ZsDataStoreOptions storeOptions_;
    };
}
#endif
