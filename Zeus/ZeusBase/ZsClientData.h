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
        ZsClientDataHeartbeat   = 0,
        ZsClientDataAdd         = 1,
        ZsClientDataRemove      = 2,
        ZsClientDataCreate      = 3,
    };

    class ZsClientData: public BalSerializeComponent
    {
    public:
        BalPackUInt8 type_;
        BalPackArray<ZsClientDataAddr> array_;

    public:
        bool DumpOut() const;
        bool SetDataType(uint8_t type);

    public:
        int Size();
        int Serialize(std::string& str, bool endian);
        int Serialize(char* buffer, uint32_t capacity, bool endian);
        int UnSerialize(char* buffer, uint32_t capacity, bool endian);
    };
}
#endif
