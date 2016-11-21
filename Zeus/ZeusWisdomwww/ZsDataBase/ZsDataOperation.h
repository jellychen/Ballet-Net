#ifndef Zeus_ZeusCollocation_ZsDataBase_ZsDataOperation_H
#define Zeus_ZeusCollocation_ZsDataBase_ZsDataOperation_H
#include <Ballet/Common/BalInct.h>
using namespace Ballet;

namespace Zeus
{
    enum ZsDataOperation
    {
        ZsNone          = 0,
        ZsSet           = 1,
        ZsDelete        = 2,
        ZsExistSet      = 3,
        ZsNotExistSet   = 4,
    };

    class ZsDataOperationPack
    {
    public:
        ZsDataOperationPack();

    public:
        uint64_t term_;
        uint8_t operation_;
        std::string key_, value_;

    public:
        void DumpToString(std::string&);
        void ConvertFromString(std::string&);
    };
}
#endif
