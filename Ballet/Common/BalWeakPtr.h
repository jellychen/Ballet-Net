#ifndef Ballet_Common_BalWeakPtr_H
#define Ballet_Common_BalWeakPtr_H
#include "BalBase.h"
#include "BalSharePtr.h"

namespace Ballet
{
    namespace Common
    {
        template<typename T> class BalWeakPtr :public BalBasePtr<T>
        {
        public:
            BalWeakPtr() throw()
            {

            }

            BalWeakPtr(const BalWeakPtr<T>& ptr) throw()
            {
                this->ownerShip_ = ptr.ownerShip_;
                if (__nullptr() != this->ownerShip_)
                {
                    this->ownerShip_->WeakRetain();
                }
            }

            BalWeakPtr(const BalSharePtr<T>& ptr) throw()
            {
                this->ownerShip_ = ptr.ownerShip_;
                if (__nullptr() != this->ownerShip_)
                {
                    this->ownerShip_->WeakRetain();
                }
            }

            virtual ~BalWeakPtr()
            {
                ReleaseMemory();
            }
        public:
            void ReleaseMemory()
            {
                if (__nullptr() != this->ownerShip_)
                {
                    this->ownerShip_->WeakRelease();
                    this->ownerShip_ = __nullptr();
                }
            }

            void operator= (int _null) throw()
            {
                ReleaseMemory();
            }

            void operator= (const BalWeakPtr<T>& ptr)
            {
                if (ptr.HashCode() == this->HashCode())
                {
                    return;
                }

                ReleaseMemory();
                this->ownerShip_ = ptr.ownerShip_;
                if (__nullptr() != this->ownerShip_)
                {
                    this->ownerShip_->WeakRetain();
                }
            }

            void operator= (const BalSharePtr<T>& ptr)
            {
                if (ptr.HashCode() == this->HashCode())
                {
                    return;
                }

                ReleaseMemory();
                this->ownerShip_ = ptr.ownerShip_;
                if (__nullptr() != this->ownerShip_)
                {
                    this->ownerShip_->WeakRetain();
                }
            }

        private:
            friend class BalSharePtr<T>;
        };
    }
}
#endif
