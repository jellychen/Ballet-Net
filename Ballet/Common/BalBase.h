#ifndef Ballet_Common_BalBase_H
#define Ballet_Common_BalBase_H
#include "BalInct.h"
#include "BalNull.h"
#include "BalOwnerShip.h"

namespace Ballet
{
    namespace Common
    {
        class BalBase
        {
        public:
            virtual long HashCode() = 0;
            virtual void ReleaseMemory() = 0;
        };

        template<typename T> class BalBaseImplement :public T
        {
        public:
            static BalBaseImplement<T>* CreateInstance()
            {
                return new(std::nothrow)BalBaseImplement<T>();
            }

        public:
            BalBaseImplement()
            {
                try
                {
                    ownerShip_ = BalOwnerShip<T>::CreateInstance(this);
                }
                catch(std::exception error)
                {
                    throw error;
                }

                if (__nullptr() == ownerShip_)
                {
                    throw std::runtime_error("BalBaseImplement Construct Create OwnerShip Failed");
                }
            }

            void ReleaseMemory()
            {
                delete this;
            }

            long HashCode()
            {
                return (long)(this);
            }
        public:
            BalOwnerShip<T>* ownerShip_;
        };
    }
}
#endif
