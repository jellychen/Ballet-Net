#ifndef Ballet_Common_BalOwnerShip_H
#define Ballet_Common_BalOwnerShip_H
#include "BalInct.h"
#include "BalBase.h"
#include "BalNull.h"
#include "BalCoable.h"

namespace Ballet
{
    namespace Common
    {
        template<typename T> class BalBaseImplement;
        template<typename T> class BalOwnerShip :public BalNoCoable
        {
        public:
            long ref_, objectRef_; T* object_;

        public:
            BalOwnerShip(T* object):ref_(0), objectRef_(0), object_(object)
            {
                if (__nullptr() == object_)
                {
                    throw std::runtime_error("BalOwnerShip Construct Failed");
                }
            }

        public:
            static BalOwnerShip<T>* CreateInstance(T* object)
            {
                if (__nullptr() == object)
                {
                    return __nullptr();
                }
                return new(std::nothrow)BalOwnerShip<T>(object);
            }

        public:
            void Retain() { ++ref_; ++objectRef_;}
            void WeakRetain() { ++ref_;}

            void Release()
            {
                --ref_; --objectRef_;

                if (0 == objectRef_ && object_)
                {
                    object_->ReleaseMemory();
                    object_ = __nullptr();
                }

                if (0 == ref_)
                {
                    delete this;
                }
            }

            void WeakRelease()
            {
                --ref_;

                if (0 == ref_)
                {
                    delete this;
                }
            }

            void ReleaseMemory()
            {
                if (__nullptr() != object_)
                {
                    object_->ReleaseMemory();
                }
                delete this;
            }

            long ObjectHashCode()
            {
                if (__nullptr() == object_)
                {
                    return 0;
                }
                object_->HashCode();
            }
        };
    }
}
#endif
