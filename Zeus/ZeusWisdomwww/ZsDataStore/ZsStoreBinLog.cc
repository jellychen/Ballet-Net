#include "ZsStoreBinLog.h"
using namespace Zeus;

const std::string _g_logData = "binlog-db";
const std::string _g_logDataStartIndex = "sys:binlog-start";
const std::string _g_logDataLengthIndex = "sys:binlog-length";

ZsStoreBinLog::ZsStoreBinLog(const char* dir, ZsDataStoreOptions& opt)
{
    workDir_ = dir; storeOptions_ = opt;
    if (false == BalDirUtil::IsPathExist(workDir_.c_str()))
    {
        if (false == BalDirUtil::CreateDir(workDir_.c_str()))
        {
            throw std::runtime_error("ZsStoreBinLog CreateDir Failed!");
        }
    }
    start_ = 0; len_ = 0; lastTerm_ = 0;

    leveldb::Options dbOptions;
    if (storeOptions_.compress_)
    {
        dbOptions.compression = leveldb::kSnappyCompression;
    }
    dbOptions.create_if_missing = true;
    dbOptions.block_size = storeOptions_.blockSize_;
    dbOptions.write_buffer_size = storeOptions_.writeBufferSize_;

    leveldb::DB* dbPointer = nullptr_();
    std::string absolutePath = workDir_ + _g_logData;
    leveldb::Status status = leveldb::DB::Open(dbOptions, absolutePath, &dbPointer);
    if (nullptr_() == dbPointer)
    {
        throw std::runtime_error("ZsStoreBinLog CreateDataBase Failed!");
    }
    BalHandle<leveldb::DB> dbHandle(dbPointer); dbHandle_ = dbHandle;

    ZsStoreBinLog::LoadInfoFormDataBase();
}

ZsStoreBinLog::~ZsStoreBinLog()
{

}

bool ZsStoreBinLog::AppendSlot(ZsDataOperationPack& pack)
{
    if (!dbHandle_) return false;
    std::string packStr;
    pack.DumpToString(packStr);
    leveldb::WriteBatch batch;
    batch.Put(ZsUInt64ToString(start_ + len_), packStr);
    batch.Put(_g_logDataLengthIndex, ZsUInt64ToString(len_ + 1));
    leveldb::Status status = dbHandle_->Write(leveldb::WriteOptions(), &batch);
    assert(status.ok()); len_++; lastTerm_ = pack.term_;
    return true;
}

bool ZsStoreBinLog::GetSlotAtIndex(uint64_t index, ZsDataOperationPack* pack)
{
    if (!dbHandle_) return false;
    if (nullptr_() == pack) return false;
    std::string key = ZsUInt64ToString(index), packStr;
    leveldb::Status status = dbHandle_->Get(leveldb::ReadOptions(), key, &packStr);
    if (!status.ok() || packStr.empty()) return false;
    pack->ConvertFromString(packStr);
    return true;
}

bool ZsStoreBinLog::DelSlotAtIndex(uint64_t index)
{
    if (!dbHandle_) return false;
    std::string key = ZsUInt64ToString(index);
    return dbHandle_->Delete(leveldb::WriteOptions(), key).ok();
}

bool ZsStoreBinLog::DelSlotBeforIndex(uint64_t index)
{
    if (index <= start_ || !dbHandle_) return false;
    uint64_t num = 0; leveldb::WriteBatch batch;
    for (uint64_t i = start_ ; i < index; ++i)
    {
        num++; batch.Delete(ZsUInt64ToString(i));
    }

    leveldb::Status status = dbHandle_->Write(leveldb::WriteOptions(), &batch);
    if (status.ok())
    {
        start_ = index; len_ -= num; return true;
    }
    return false;
}

bool ZsStoreBinLog::TruncateSlotAtIndex(uint64_t index)
{
    if (!dbHandle_) return false;
    if (index < start_ || index > (start_ + len_ -1))
    {
        return false;
    }

    uint64_t newLen = index - start_ + 1;
    leveldb::Status status = dbHandle_->Put(leveldb::WriteOptions(),
        _g_logDataLengthIndex, ZsUInt64ToString(newLen));
    return status.ok();
}

bool ZsStoreBinLog::GetLastIndexAndTerm(uint64_t* index, uint64_t* term)
{
    if (nullptr_() != index)
    {
        *index = start_ + len_ -1;
    }

    if (nullptr_() != term)
    {
        *term = lastTerm_;
    }
    return true;
}

uint64_t ZsStoreBinLog::GetBinLen() const
{
    return len_;
}

void ZsStoreBinLog::LoadInfoFormDataBase()
{
    if (!dbHandle_) return;
    leveldb::Status status; std::string lenStr = "";
    status = dbHandle_->Get(leveldb::ReadOptions(), _g_logDataLengthIndex, &lenStr);
    if (!status.ok() || lenStr.empty()) return;
    len_ = ZsStringToUInt64(lenStr);

    std::string startStr = "";
    status = dbHandle_->Get(leveldb::ReadOptions(), _g_logDataStartIndex, &startStr);
    if (status.ok() && !startStr.empty())
    {
        start_ = ZsStringToUInt64(startStr);
    }

    if (len_ > 0)
    {
        ZsDataOperationPack logPack;
        assert(ZsStoreBinLog::GetSlotAtIndex(start_ + len_ -1, &logPack));
        lastTerm_ = logPack.term_;
    }
}
