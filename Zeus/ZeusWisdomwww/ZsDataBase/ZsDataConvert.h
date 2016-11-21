#ifndef Zeus_ZeusCollocation_ZsDataBase_ZsDataConvert_H
#define Zeus_ZeusCollocation_ZsDataBase_ZsDataConvert_H
#include <Ballet/Common/BalInct.h>
using namespace Ballet;

namespace Zeus
{
    inline uint64_t ZsStringToUInt64(std::string& str)
    {
        uint64_t _t = 0;
        ::sscanf(str.c_str(), "%I64u", &_t);
        return _t;
    }

    inline std::string ZsUInt64ToString(uint64_t data)
    {
        char buffer[128] = {0};
        ::sprintf(buffer, "%I64u", data);
        std::string str = buffer;
        return str;
    }
}
#endif
