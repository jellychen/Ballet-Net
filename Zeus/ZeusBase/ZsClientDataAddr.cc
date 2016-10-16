#include "ZsClientDataAddr.h"
using namespace std;
using namespace Zeus;

int ZsClientDataAddr::Size()
{
    return name_.Size() + address_.Size();
}

int ZsClientDataAddr::Serialize(std::string& str, bool endian)
{
    int size = 0, writeSize = 0;
    do
    {
        writeSize = name_.Serialize(str, endian);
        if (-1 == writeSize) break; size += writeSize;
        writeSize = address_.Serialize(str, endian);
        if (-1 == writeSize) break; size += writeSize;

        return size;
    } while (0);
    return -1;
}

int ZsClientDataAddr::Serialize(char* buffer, uint32_t capacity, bool endian)
{
    int size = 0, writeSize = 0;
    do
    {
        writeSize = name_.Serialize(buffer, capacity, endian);
        if (-1 == writeSize) break;
        size += writeSize; capacity -= writeSize; buffer += writeSize;
        writeSize = address_.Serialize(buffer, capacity, endian);
        if (-1 == writeSize) break; size += writeSize;

        return size;
    } while (0);
    return -1;
}

int ZsClientDataAddr::UnSerialize(char* buffer, uint32_t capacity, bool endian)
{
    int size = 0, readSize = 0;
    do
    {
        readSize = name_.UnSerialize(buffer, capacity, endian);
        if (-1 == readSize) break;
        size += readSize; capacity -= readSize; buffer += readSize;
        readSize = address_.UnSerialize(buffer, capacity, endian);
        if (-1 == readSize) break; size += readSize;

        return size;
    } while (0);
    return -1;
}
