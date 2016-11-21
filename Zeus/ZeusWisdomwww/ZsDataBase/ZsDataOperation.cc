#include "ZsDataOperation.h"
using namespace Zeus;

ZsDataOperationPack::ZsDataOperationPack()
{
    term_ = 0; operation_ = ZsNone;
}

void ZsDataOperationPack::DumpToString(std::string& str)
{
    uint32_t len = 0;
    len += sizeof(uint64_t) + sizeof(uint8_t);
    len += sizeof(uint32_t) + sizeof(uint32_t);
    len += key_.size() + value_.size();
    str.resize(len);

    char* buffer = reinterpret_cast<char*>(&(str[0]));
    memcpy(buffer, (void*)(&term_), sizeof(uint64_t)); buffer += sizeof(uint64_t);
    memcpy(buffer, (void*)(&operation_), sizeof(uint8_t)); buffer += sizeof(uint8_t);
    uint32_t keySize = (uint32_t)(key_.size());
    memcpy(buffer, (void*)(&keySize), sizeof(uint32_t)); buffer += sizeof(uint32_t);
    memcpy(buffer, key_.c_str(), keySize); buffer += keySize;
    uint32_t valueSize = (uint32_t)(value_.size());
    memcpy(buffer, (void*)(&valueSize), sizeof(uint32_t)); buffer += sizeof(uint32_t);
    memcpy(buffer, value_.c_str(), valueSize); buffer += valueSize;
}

void ZsDataOperationPack::ConvertFromString(std::string& str)
{
    uint32_t len = (uint32_t)(str.size());
    char* buffer = reinterpret_cast<char*>(&(str[0]));

    if (len < sizeof(uint64_t)) return;
    memcpy((void*)(&term_), buffer, sizeof(uint64_t));
    buffer += sizeof(uint64_t); len -= sizeof(uint64_t);
    if (len < sizeof(uint8_t)) return;
    memcpy((void*)(&operation_), buffer, sizeof(uint8_t));
    buffer += sizeof(uint8_t); len -= sizeof(uint8_t);

    if (len < sizeof(uint32_t)) return;
    uint32_t keySize = 0;
    memcpy((void*)(&keySize), buffer, sizeof(uint32_t));
    buffer += sizeof(uint32_t); len -= sizeof(uint32_t);
    if (len < keySize) return;
    key_.resize(keySize);
    memcpy((void*)(&(key_[0])), buffer, keySize);
    buffer += keySize; len -= keySize;

    if (len < sizeof(uint32_t)) return;
    uint32_t valueSize = 0;
    memcpy((void*)(&valueSize), buffer, sizeof(uint32_t));
    buffer += sizeof(uint32_t); len -= sizeof(uint32_t);
    if (len < valueSize) return;
    value_.resize(valueSize);
    memcpy((void*)(&(value_[0])), buffer, valueSize);
}
