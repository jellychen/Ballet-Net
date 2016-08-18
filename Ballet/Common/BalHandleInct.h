#ifndef Ballet_Common_BalHandleInct_H
#define Ballet_Common_BalHandleInct_H
#include "BalHandle.h"
#include "BalWeakHandle.h"

namespace Ballet
{
    template<class T, class U>
    inline bool operator== (const BalHandle<T>& l, const BalHandle<U>& r) throw()
    {
        return (l.HashCode() == r.HashCode());
    }

    template<class T, class U>
    inline bool operator!= (const BalHandle<T>& l, const BalHandle<U>& r) throw()
    {
        return (l.HashCode() != r.HashCode());
    }

    template<class T, class U>
    inline bool operator== (const BalHandle<T>& l, const BalWeakHandle<U>& r) throw()
    {
        return (l.HashCode() == r.HashCode());
    }

    template<class T, class U>
    inline bool operator!= (const BalHandle<T>& l, const BalWeakHandle<U>& r) throw()
    {
        return (l.HashCode() != r.HashCode());
    }

    template<class T, class U>
    inline bool operator== (const BalWeakHandle<T>& l, const BalHandle<U>& r) throw()
    {
        return (l.HashCode() == r.HashCode());
    }

    template<class T, class U>
    inline bool operator!= (const BalWeakHandle<T>& l, const BalHandle<U>& r) throw()
    {
        return (l.HashCode() != r.HashCode());
    }

    template<class T, class U>
    inline bool operator== (const BalWeakHandle<T>& l, const BalWeakHandle<U>& r) throw()
    {
        return (l.HashCode() == r.HashCode());
    }

    template<class T, class U>
    inline bool operator!= (const BalWeakHandle<T>& l, const BalWeakHandle<U>& r) throw()
    {
        return (l.HashCode() != r.HashCode());
    }
}
#endif
