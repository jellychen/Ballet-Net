#include "ZsClientDataAddr.h"
using namespace std;
using namespace Zeus;

ZsClientDataAddr::ZsClientDataAddr()
{

}

bool ZsClientDataAddr::AssignData(const char* name, const char* addr)
{
    if (!name || !addr) return false;
    name_.assign(name); address_.assign(addr);
    return true;
}

int ZsClientDataAddr::Size()
{
    return name_.Size() + address_.Size();
}

int ZsClientDataAddr::Serialize(std::string& str, bool endian)
{
    int size = 0, write = 0;
    do
    {
        write = name_.Serialize(str, endian);
        if (-1 == write) break; size += write;
        write = address_.Serialize(str, endian);
        if (-1 == write) break; size += write;

        return size;
    } while (0);
    return -1;
}

int ZsClientDataAddr::Serialize(char* buffer, uint32_t capacity, bool endian)
{
    int size = 0, write = 0;
    do
    {
        write = name_.Serialize(buffer, capacity, endian);
        if (-1 == write) break;
        size += write; capacity -= write; buffer += write;
        write = address_.Serialize(buffer, capacity, endian);
        if (-1 == write) break; size += write;

        return size;
    } while (0);
    return -1;
}

int ZsClientDataAddr::UnSerialize(char* buffer, uint32_t capacity, bool endian)
{
    int size = 0, read = 0;
    do
    {
        read = name_.UnSerialize(buffer, capacity, endian);
        if (-1 == read) break;
        size += read; capacity -= read; buffer += read;
        read = address_.UnSerialize(buffer, capacity, endian);
        if (-1 == read) break; size += read;

        return size;;
    } while (0);
    return -1;
}
