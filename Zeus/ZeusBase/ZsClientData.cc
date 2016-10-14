#include "ZsClientData.h"
using namespace std;
using namespace Zeus;

ZsClientData::ZsClientData()
{

}

int ZsClientData::Size()
{
    return type_.Size() + array_.Size();
}

int ZsClientData::Serialize(std::string& str, bool endian)
{
    int size = 0, write = 0;
    do
    {
        write = type_.Serialize(str, endian);
        if (-1 == write) break; size += write;
        write = array_.Serialize(str, endian);
        if (-1 == write) break; size += write;

        return size;
    } while (0);
    return -1;
}

int ZsClientData::Serialize(char* buffer, uint32_t capacity, bool endian)
{
    int size = 0, write = 0;
    do
    {
        write = type_.Serialize(buffer, capacity, endian);
        if (-1 == write) break;
        size += write; capacity -= write; buffer += write;
        write = array_.Serialize(buffer, capacity, endian);
        if (-1 == write) break; size += write;

        return size;
    } while (0);
    return -1;
}

int ZsClientData::UnSerialize(char* buffer, uint32_t capacity, bool endian)
{
    int size = 0, read = 0;
    do
    {
        read = type_.UnSerialize(buffer, capacity, endian);
        if (-1 == read) break;
        size += read; capacity -= read; buffer += read;
        read = array_.UnSerialize(buffer, capacity, endian);
        if (-1 == read) break; size += read;

        return size;;
    } while (0);
    return -1;
}
