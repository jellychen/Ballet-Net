#ifndef Ballet_Network_BalNetDefine_H
#define Ballet_Network_BalNetDefine_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace Network
    {
        static const int      MAX_READFD_SIZE           =10240;
        static const uint32_t MAX_READ_BUFFER_SIZE      =102400;
        static const uint32_t MAX_WRITE_BUFFER_SIZE     =102400;
        static const uint32_t MAX_EVENTDATA_CACHE       =100000;
    }
}
#endif
