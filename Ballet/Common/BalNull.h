#ifndef Ballet_Common_BalNull_H
#define Ballet_Common_BalNull_H

namespace Ballet
{
    struct BalNull
    {
        template<typename T> operator T*() const
        {
            return 0;
        }
    };

    inline BalNull& nullptr_()
    {
        static BalNull nil = {};
        return nil;
    }
}
#endif
