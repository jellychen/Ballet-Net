#ifndef Ballet_Common_BalBuffer_H
#define Ballet_Common_BalBuffer_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace Network
    {
        class BalBuffer :public BalNoCoable
        {
        public:
            BalBuffer();
            virtual ~BalBuffer();
        };
    }
}
#endif
