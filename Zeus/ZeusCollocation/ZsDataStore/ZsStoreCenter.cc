#include "ZsStoreCenter.h"
using namespace Zeus;

ZsStoreCenter::ZsStoreCenter(const char* dir, ZsDataStoreOptions& opt)
{
    workDir_ = dir; storeOptions_ = opt;

    if (!BalDirUtil::CreateDir(dir))
    {
        throw std::runtime_error("ZsStoreCenter CreateDir Failed");
    }
}

ZsStoreCenter::~ZsStoreCenter()
{

}

bool ZsStoreCenter::LoadDatabase(const char* database)
{
    if (!database) return false;

    if (true)
    {
        BalMutexWatcher watcher(&mutex_);
        if (dbPool_.end() != dbPool_.find(database))
        {
            return true;
        }
    }

    std::string absolutePath = workDir_ + database + "-db";
    leveldb::Options dbOptions;
    if (storeOptions_.compress_)
    {
        dbOptions.compression = leveldb::kSnappyCompression;
    }
    dbOptions.block_size = storeOptions_.blockSize_;
    dbOptions.write_buffer_size = storeOptions_.writeBufferSize_;

    leveldb::DB* dbPointer = nullptr_();
    leveldb::Status status = leveldb::DB::Open(dbOptions, absolutePath, &dbPointer);

    if (dbPointer)
    {
        BalMutexWatcher watcher(&mutex_);
        BalHandle<leveldb::DB> dbHandle(dbPointer);
        dbPool_[database] = dbHandle;
    }
    return status.ok();
}

bool ZsStoreCenter::CloseDatabase(const char* database)
{
    if (!database) return false;
    BalMutexWatcher watcher(&mutex_);
    dbPoolT::iterator iter = dbPool_.find(database);

    if (dbPool_.end() == iter)
    {
        return true;
    }
    dbPool_.erase(iter);
    return true;
}
