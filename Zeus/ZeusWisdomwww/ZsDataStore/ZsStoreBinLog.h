#ifndef Zeus_ZeusCollocation_ZsDataStore_ZsStoreBinLog_H
#define Zeus_ZeusCollocation_ZsDataStore_ZsStoreBinLog_H
#include <leveldb/db.h>
#include <leveldb/write_batch.h>
#include <Ballet/Common/BalInct.h>
#include <Ballet/BootUtil/BalDirUtil.h>
#include <Ballet/BootUtil/BalMutexWatcher.h>
using namespace Ballet;
using namespace BootUtil;

#include "ZsDataStoreOptions.h"
#include "ZsDataBase/ZsDataConvert.h"
#include "ZsDataBase/ZsDataOperation.h"

namespace Zeus
{
    class ZsStoreBinLog: public BalNoCoable
    {
    public:
        ZsStoreBinLog(const char*, ZsDataStoreOptions&);
        virtual ~ZsStoreBinLog();

    public:
        bool AppendSlot(ZsDataOperationPack&);
        bool GetSlotAtIndex(uint64_t, ZsDataOperationPack*);
        bool DelSlotAtIndex(uint64_t);
        bool DelSlotBeforIndex(uint64_t);
        bool TruncateSlotAtIndex(uint64_t);
        bool GetLastIndexAndTerm(uint64_t*, uint64_t*);

    public:
        uint64_t GetBinLen() const;

    private:
        void LoadInfoFormDataBase();

    public:
        std::string workDir_;
        uint64_t start_, len_, lastTerm_;
        ZsDataStoreOptions storeOptions_;
        BalHandle<leveldb::DB> dbHandle_;
    };
}
#endif
