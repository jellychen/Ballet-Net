#ifndef Ballet_Common_BalSharePtr_H
#define Ballet_Common_BalSharePtr_H
#include "BalBasePtr.h"

namespace Ballet
{
    namespace Common
    {
        template<typename T> class BalWeakPtr;
        template<typename T> class BalSharePtr :public BalBasePtr<T>
        {
        public:
            BalSharePtr() throw()
            {
            }

            BalSharePtr(const BalSharePtr<T>& ptr) throw()
            {
                this->ownerShip_ = ptr.ownerShip_;
                if (__nullptr() != this->ownerShip_)
                {
                    this->ownerShip_->Retain();
                }
            }

            BalSharePtr(const BalWeakPtr<T> ptr) throw()
            {
                this->ownerShip_ = ptr.ownerShip_;
                if (__nullptr() != this->ownerShip_)
                {
                    this->ownerShip_->Retain();
                }
            }

            BalSharePtr(const BalBaseImplement<T>* basePtr) throw()
            {
                if (__nullptr() == basePtr)
                {
                    this->ownerShip_ = __nullptr();
                }
                else
                {
                    this->ownerShip_ = basePtr->ownerShip_;
                    if (__nullptr() != this->ownerShip_)
                    {
                        this->ownerShip_->Retain();
                    }
                }
            }

            virtual ~BalSharePtr()
            {
                ReleaseMemory();
            }

        public:
            bool NewInstance()
            {
                ReleaseMemory();

                BalBaseImplement<T>* instance = new(std::nothrow)BalBaseImplement<T>();
                if (__nullptr() == instance)
                {
                    return false;
                }

                this->ownerShip_ = instance->ownerShip_;
                if (__nullptr() != this->ownerShip_)
                {
                    this->ownerShip_->Retain();
                }
            }

            void ReleaseMemory()
            {
                if (__nullptr() != this->ownerShip_)
                {
                    this->ownerShip_->Release();
                    this->ownerShip_ = __nullptr();
                }
            }

            void operator= (int _null) throw()
            {
                ReleaseMemory();
            }

            void operator= (const BalBaseImplement<T>* basePtr)
            {
                if (__nullptr() != basePtr && this->HashCode() == basePtr->HashCode())
                {
                    return;
                }

                ReleaseMemory();

                if (__nullptr() != basePtr)
                {
                    this->ownerShip_ = basePtr->ownerShip_;
                }

                if (__nullptr() != this->ownerShip_)
                {
                    this->ownerShip_->Retain();
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
                    this->ownerShip_->Retain();
                }
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
                    this->ownerShip_->Retain();
                }
            }

        private:
            friend class BalWeakPtr<T>;
        };
    }
}
#endif
