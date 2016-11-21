#ifndef Zeus_ZeusCollocation_ZsDataStore_ZsStorePersistent_H
#define Zeus_ZeusCollocation_ZsDataStore_ZsStorePersistent_H
#include <leveldb/db.h>
#include <leveldb/write_batch.h>
#include <Ballet/Common/BalInct.h>
#include <Ballet/BootUtil/BalDirUtil.h>
using namespace Ballet;
using namespace BootUtil;

#include "ZsDataStoreOptions.h"
#include "ZsDataBase/ZsDataConvert.h"

namespace Zeus
{
    class ZsStorePersistent: public BalNoCoable
    {
    public:
        ZsStorePersistent(const char*, ZsDataStoreOptions&);
        virtual ~ZsStorePersistent();

    public:
        bool Set(std::string& key, std::string& value);
        bool Get(std::string& key, std::string& value);
        bool Delete(std::string& key);

    private:
        std::string workDir_;
        ZsDataStoreOptions storeOptions_;
        BalHandle<leveldb::DB> dbHandle_;
    };
}
#endif
