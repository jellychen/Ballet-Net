#ifndef Ballet_Common_BalBuffer_H
#define Ballet_Common_BalBuffer_H
#include "../Common/BalCoable.h"

namespace Ballet
{
    namespace Network
    {
        class s{};
        class BalBuffer :public Common::BalNoCoable, public s
        {
        public:
            BalBuffer();
            virtual ~BalBuffer();

            static BalBuffer* Create()
            {
                return new BalBuffer();
            }
        };
    }
}
#endif
