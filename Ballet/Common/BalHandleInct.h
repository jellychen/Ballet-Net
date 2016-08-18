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

    template<class T, class U>
    BalHandle<T> static_cast_(const BalHandle<U>& ptr)
    {
        return BalHandle<T>(ptr, static_cast_<T*>(ptr.GetBasePtr()));
    }

    template<class T, class U>
    BalHandle<T> dynamic_cast_(const BalHandle<U>& ptr)
    {
        return BalHandle<T>(ptr, dynamic_cast<T*>(ptr.GetBasePtr()));
    }

    template<class T, class U>
    BalWeakHandle<T> static_cast_(const BalWeakHandle<U>& ptr)
    {
        return BalWeakHandle<T>(ptr, static_cast_<T*>(ptr.GetBasePtr()));
    }

    template<class T, class U>
    BalWeakHandle<T> dynamic_cast_(const BalWeakHandle<U>& ptr)
    {
        return BalWeakHandle<T>(ptr, dynamic_cast<T*>(ptr.GetBasePtr()));
    }
}
#endif
