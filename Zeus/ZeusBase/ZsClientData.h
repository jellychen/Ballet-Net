#ifndef Zeus_ZeusBase_ZsClientData_H
#define Zeus_ZeusBase_ZsClientData_H
#include <Ballet/Common/BalInct.h>
#include <Ballet/BootUtil/BalSerialize.h>
using namespace Ballet;
using namespace BootUtil;

#include "ZsClientDataAddr.h"

namespace Zeus
{
    enum ZsClientDataType
    {
        ZsClientDataAdd     = 0,
        ZsClientDataRemove  = 1,
        ZsClientDataReload  = 2,
    };

    class ZsClientData: public BalSerializeComponent
    {
    public:
        ZsClientData();

    public:
        BalPackUInt8 type_;
        BalPackArray<ZsClientDataAddr> array_;

    public:
        int Size();
        int Serialize(std::string& str, bool endian);
        int Serialize(char* buffer, uint32_t capacity, bool endian);
        int UnSerialize(char* buffer, uint32_t capacity, bool endian);
    };
}
#endif
