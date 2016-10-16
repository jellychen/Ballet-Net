#ifndef Zeus_ZeusBase_ZsClientDataAddr_H
#define Zeus_ZeusBase_ZsClientDataAddr_H
#include <Ballet/Common/BalInct.h>
#include <Ballet/BootUtil/BalSerialize.h>
using namespace Ballet;
using namespace BootUtil;

namespace Zeus
{
    class ZsClientDataAddr: public BalSerializeComponent
    {
    public:
        BalPackString name_;
        BalPackArray<BalPackString> address_;

    public:
        int Size();
        int Serialize(std::string& str, bool endian);
        int Serialize(char* buffer, uint32_t capacity, bool endian);
        int UnSerialize(char* buffer, uint32_t capacity, bool endian);
    };
}
#endif
