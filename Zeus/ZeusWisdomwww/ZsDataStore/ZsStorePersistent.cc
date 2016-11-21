#include "ZsStorePersistent.h"
using namespace Zeus;

const std::string _g_persistent = "store-db";

ZsStorePersistent::ZsStorePersistent(const char* dir, ZsDataStoreOptions& opt)
{
    workDir_ = dir; storeOptions_ = opt;
    if (false == BalDirUtil::IsPathExist(workDir_.c_str()))
    {
        if (false == BalDirUtil::CreateDir(workDir_.c_str()))
        {
            throw std::runtime_error("ZsStorePersistent CreateDir Failed!");
        }
    }

    leveldb::Options dbOptions;
    if (storeOptions_.compress_)
    {
        dbOptions.compression = leveldb::kSnappyCompression;
    }
    dbOptions.create_if_missing = true;
    dbOptions.block_size = storeOptions_.blockSize_;
    dbOptions.write_buffer_size = storeOptions_.writeBufferSize_;

    leveldb::DB* dbPointer = nullptr_();
    std::string absolutePath = workDir_ + _g_persistent;
    leveldb::Status status = leveldb::DB::Open(dbOptions, absolutePath, &dbPointer);
    if (nullptr_() == dbPointer)
    {
        throw std::runtime_error("ZsStorePersistent CreateDataBase Failed!");
    }
    BalHandle<leveldb::DB> dbHandle(dbPointer); dbHandle_ = dbHandle;
}

ZsStorePersistent::~ZsStorePersistent()
{

}

bool ZsStorePersistent::Set(std::string& key, std::string& value)
{
    if (!dbHandle_) return false;
    return dbHandle_->Put(leveldb::WriteOptions(), key, value).ok();
}

bool ZsStorePersistent::Get(std::string& key, std::string& value)
{
    if (!dbHandle_) return false;
    return dbHandle_->Get(leveldb::ReadOptions(), key, &value).ok();
}

bool ZsStorePersistent::Delete(std::string& key)
{
    if (!dbHandle_) return false;
    return dbHandle_->Delete(leveldb::WriteOptions(), key).ok();
}
