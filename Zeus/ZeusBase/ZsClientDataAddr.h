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
        ZsClientDataAddr();

    public:
        BalPackString name_;
        BalPackString address_;

    public:
        bool AssignData(const char*, const char*);

    public:
        int Size();
        int Serialize(std::string& str, bool endian);
        int Serialize(char* buffer, uint32_t capacity, bool endian);
        int UnSerialize(char* buffer, uint32_t capacity, bool endian);
    };
}
#endif
