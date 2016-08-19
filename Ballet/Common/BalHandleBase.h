#ifndef Ballet_Common_BalHandleBase_H
#define Ballet_Common_BalHandleBase_H
#include "BalUseCount.h"
#include "BalShareThis.h"

namespace Ballet
{
    template<typename T> class BalHandleBase
    {
    public:
        BalHandleBase() throw():object_(0),useCount_(0)
        {
        }

        inline operator bool() const throw()
        {
            return useCount_ && useCount_->IsAlived();
        }

        inline T* operator->() const throw()
        {
            return object_;
        }

        inline T& operator*() const throw()
        {
            return *object_;
        }

    public:
        inline long HashCode() const throw()
        {
            if (useCount_)
            {
                return useCount_->HashCode();
            }
            return 0;
        }

        inline long UseCount() const throw()
        {
            if (useCount_)
            {
                return useCount_->UseCount();
            }
            return 0;
        }

        inline T* GetBasePtr() const throw()
        {
            return object_;
        }

    protected:
        T* object_;
        BalUseCount* useCount_;
    };
}
#endif
