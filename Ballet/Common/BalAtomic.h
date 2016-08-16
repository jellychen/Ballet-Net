#ifndef Ballet_Common_BalAtomic_H
#define Ballet_Common_BalAtomic_H

namespace Ballet
{
    namespace Common
    {
        template<typename T> class TBalAtomicInt :public BalNoCoable
        {
            volatile T t_;

        public:
            TBalAtomicInt():t_(0) {}
        public:
            T Get()
            {
                return __sync_val_compare_and_swap(&t_, 0, 0);
            }

            T Set(T x)
            {
                return __sync_lock_test_and_set(&t_, x);
            }

            T Increment()
            {
                return AddAndGet(1);
            }

            T Decrement()
            {
                return AddAndGet(-1);
            }

            T GetAndAdd(T x)
            {
                return __sync_fetch_and_add(&t_, x);
            }

            T AddAndGet(T x)
            {
                return __sync_fetch_and_add(&t_, x) + x;
            }

            T GetAndSet(T x)
            {
                return __sync_lock_test_and_set(&t_, x);
            }
        };

        typedef TBalAtomicInt<int32_t> BalAtomicInt32;
        typedef TBalAtomicInt<int64_t> BalAtomicInt64;
    }
}
#endif
