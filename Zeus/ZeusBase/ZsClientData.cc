#include "ZsClientData.h"
using namespace std;
using namespace Zeus;

bool ZsClientData::DumpOut() const
{
    if (ZsClientDataAdd == type_)
    {
        printf("type: ZsClientDataAdd\n");
    }
    else if (ZsClientDataRemove == type_)
    {
        printf("type: ZsClientDataRemove\n");
    }
    else if (ZsClientDataCreate == type_)
    {
        printf("type: ZsClientDataCreate\n");
    }
    else
    {
        printf("type: 【error】\n");
    }

    for (size_t i = 0; i < array_.size(); ++i)
    {
        const ZsClientDataAddr& addr = array_.at(i);
        printf("%d %s\n", (int)i, addr.name_.c_str());
        for (size_t j = 0; j < addr.address_.size(); ++j)
        {
            printf(">   %s\n", addr.address_.at(j).c_str());
        }
    }
    return true;
}

bool ZsClientData::SetDataType(uint8_t type)
{
    type_.rawData_ = type;
    return true;
}

int ZsClientData::Size()
{
    return type_.Size() + array_.Size();
}

int ZsClientData::Serialize(std::string& str, bool endian)
{
    int size = 0, writeSize = 0;
    do
    {
        writeSize = type_.Serialize(str, endian);
        if (-1 == writeSize) break; size += writeSize;
        writeSize = array_.Serialize(str, endian);
        if (-1 == writeSize) break; size += writeSize;

        return size;
    } while (0);
    return -1;
}

int ZsClientData::Serialize(char* buffer, uint32_t capacity, bool endian)
{
    int size = 0, writeSize = 0;
    do
    {
        writeSize = type_.Serialize(buffer, capacity, endian);
        if (-1 == writeSize) break;
        size += writeSize; capacity -= writeSize; buffer += writeSize;
        writeSize = array_.Serialize(buffer, capacity, endian);
        if (-1 == writeSize) break; size += writeSize;

        return size;
    } while (0);
    return -1;
}

int ZsClientData::UnSerialize(char* buffer, uint32_t capacity, bool endian)
{
    int size = 0, readSize = 0;
    do
    {
        readSize = type_.UnSerialize(buffer, capacity, endian);
        if (-1 == readSize) break;
        size += readSize; capacity -= readSize; buffer += readSize;
        readSize = array_.UnSerialize(buffer, capacity, endian);
        if (-1 == readSize) break; size += readSize;

        return size;
    } while (0);
    return -1;
}
