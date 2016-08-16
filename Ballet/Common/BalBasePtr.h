#ifndef Ballet_Common_BalBasePtr_H
#define Ballet_Common_BalBasePtr_H
#include "BalBase.h"

namespace Ballet
{
    namespace Common
    {
        template<typename T> class BalBasePtr
        {
        public:
            BalBasePtr():ownerShip_(__nullptr())
            {
            }

        public:
            operator bool() const
            {
                return ownerShip_ && ownerShip_->object_;
            }

            bool operator!() const throw()
            {
                return !ownerShip_ || !ownerShip_->object_;
            }

            T* operator->() const throw()
            {
                return ownerShip_->object_;
            }

            T* BasePtr() const
            {
                return ownerShip_->object_;
            }

            long HashCode() const
            {
                if (__nullptr() == ownerShip_)
                {
                    return 0;
                }
                return ownerShip_->ObjectHashCode();
            }

        protected:
            BalOwnerShip<T>* ownerShip_;
        };
    }
}
#endif
