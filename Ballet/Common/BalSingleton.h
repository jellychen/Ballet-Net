#ifndef Ballet_Common_BalSingleton_H
#define Ballet_Common_BalSingleton_H
#include "BalHandleInct.h"

namespace Ballet
{
    template<class T> class BalSingleton
    {
    public:
        static BalHandle<T>& GetInstance()
        {
            if (false == BalSingleton<T>::init_)
            {
                BalSingleton<T>::init_ = true;
                BalHandle<T> instance(new T());
                BalSingleton<T>::instance_ = instance;
            }
            return BalSingleton<T>::instance_;
        }

    private:
        BalSingleton()
        {

        }

        ~BalSingleton()
        {

        }

    private:
        static bool volatile init_;
        static BalHandle<T> instance_;
    };

    template <typename T>
    BalHandle<T> BalSingleton<T>::instance_;

    template <typename T>
    bool volatile BalSingleton<T>::init_ = false;
}
#endif
