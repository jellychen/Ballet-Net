#ifndef Ballet_Common_BalSharePtr_H
#define Ballet_Common_BalSharePtr_H
#include "BalBase.h"

namespace Ballet
{
    namespace Common
    {
        template<typename T> class BalSharePtr
        {
        public:
            BalSharePtr() throw():ownerShip_(__nullptr()){}

            BalSharePtr(const BalSharePtr& ptr) throw()
            {
                ownerShip_ = ptr.ownerShip_;
                if (__nullptr() != ownerShip_)
                {
                    ownerShip_->Retain();
                }
            }

            BalSharePtr(const BalBaseImplement<T>* basePtr)
            {
                if (__nullptr() == basePtr)
                {
                    ownerShip_ = __nullptr();
                }
                else
                {
                    ownerShip_ = basePtr->ownerShip_;
                    if (__nullptr() != ownerShip_)
                    {
                        ownerShip_->Retain();
                    }
                }
            }

            ~BalSharePtr()
            {
                ReleaseMemory();
            }

        public:
            void ReleaseMemory()
            {
                if (__nullptr() != ownerShip_)
                {
                    ownerShip_->Release();
                    ownerShip_ = __nullptr();
                }
            }

            void operator= (int _null) throw()
            {
                ReleaseMemory();
            }

            void operator= (const BalBaseImplement<T>* basePtr)
            {
                ReleaseMemory();
                if (__nullptr() != basePtr)
                {
                    ownerShip_ = basePtr->ownerShip_;
                }

                if (__nullptr() != ownerShip_)
                {
                    ownerShip_->Retain();
                }
            }

            void operator= (const BalSharePtr<T>& ptr)
            {
                ReleaseMemory();
                ownerShip_ = ptr.ownerShip_;
                if (__nullptr() != ownerShip_)
                {
                    ownerShip_->Retain();
                }
            }

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

        private:
            BalOwnerShip<T>* ownerShip_;
        };
    }
}
#endif
