#ifndef Ballet_Common_BalNull_H
#define Ballet_Common_BalNull_H

namespace Ballet
{
    namespace Common
    {
        struct BalNull
        {
            template<typename t> operator t*() const
            {
                return 0;
            }
        };

        inline BalNull __nullptr()
        {
            static BalNull nil = {};
            return nil;
        }
    }
}
#endif
