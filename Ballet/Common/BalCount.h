#ifndef Ballet_Common_BalCount_H
#define Ballet_Common_BalCount_H

namespace Ballet
{
    namespace Common
    {
        class BalBase
        {
        public:
            virtual long Retain() = 0;
            virtual long Release() = 0;
            virtual long RetainCount() = 0;
        };

        template <typename T> class BalSharePtr
        {

        };

        template <typename T> class BalWeakPtr
        {

        };
    }
}
#endif
