#ifndef Zeus_ZeusCollocation_ZsDataStore_ZsDataStoreOptions_H
#define Zeus_ZeusCollocation_ZsDataStore_ZsDataStoreOptions_H
#include <Ballet/Common/BalInct.h>
using namespace Ballet;

namespace Zeus
{
    class ZsDataStoreOptions
    {
    public:
        ZsDataStoreOptions();

    public:
        bool compress_;
        int32_t blockSize_;
        int32_t writeBufferSize_;
    };
}
#endif
