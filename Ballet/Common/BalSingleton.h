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
            pthread_once(&once_, &BalSingleton::__init);
            return BalSingleton<T>::instance_;
        }

    private:
        static void __init()
        {
            BalHandle<T> instance(new T());
            BalSingleton<T>::instance_ = instance;
        }

        static pthread_once_t once_;
        static BalHandle<T> instance_;
    };

    template <typename T>
    BalHandle<T> BalSingleton<T>::instance_;

    template <typename T>
    pthread_once_t BalSingleton<T>::once_ = PTHREAD_ONCE_INIT;
}
#endif
