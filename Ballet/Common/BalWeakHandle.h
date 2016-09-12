#ifndef Ballet_Common_BalWeakHandle_H
#define Ballet_Common_BalWeakHandle_H
#include "BalHandle.h"

namespace Ballet
{
    template<typename T> class BalWeakHandle :public BalHandleBase<T>
    {
        template<typename U>
        friend class BalWeakHandle;
        friend class BalHandle<T>;
        typedef BalHandleBase<T> BaseT;
    public:
        BalWeakHandle() throw()
        {
        }

        template <typename U>
        BalWeakHandle(const BalWeakHandle<U>& handle, T* object) throw()
        {
            if (nullptr_() == object) return;
            BaseT::object_ = object;
            BaseT::useCount_ = handle.useCount_;
            BaseT::useCount_?BaseT::useCount_->AddUseCount(false):(void)0;
        }

        BalWeakHandle(const BalWeakHandle& handle) throw()
        {
            BaseT::object_ = handle.object_;
            BaseT::useCount_ = handle.useCount_;
            BaseT::useCount_?BaseT::useCount_->AddUseCount(false):(void)0;
        }

        template <typename U>
        BalWeakHandle(const BalWeakHandle<U>& handle) throw()
        {
            if (!handle) return;
            BaseT::object_ = dynamic_cast<T*>(handle.GetBasePtr());
            if (nullptr_() != BaseT::object_)
            {
                BaseT::useCount_ = handle.useCount_;
                BaseT::useCount_?BaseT::useCount_->AddUseCount(false):(void)0;
            }
        }

        BalWeakHandle(const BalHandle<T>& handle) throw()
        {
            BaseT::object_ = handle.object_;
            BaseT::useCount_ = handle.useCount_;
            BaseT::useCount_?BaseT::useCount_->AddUseCount(false):(void)0;
        }

        template <typename U>
        BalWeakHandle(const BalHandle<U>& handle) throw()
        {
            if (!handle) return;
            BaseT::object_ = dynamic_cast<T*>(handle.GetBasePtr());
            if (nullptr_() != BaseT::object_)
            {
                BaseT::useCount_ = handle.useCount_;
                BaseT::useCount_?BaseT::useCount_->AddUseCount(false):(void)0;
            }
        }

        inline ~BalWeakHandle()
        {
            this->Clear();
        }

    public:
        inline void Clear() throw()
        {
            if (nullptr_() != BaseT::object_ && nullptr_() != BaseT::useCount_)
            {
                bool del = false;
                BaseT::useCount_->DelUseCount(false, del);
                if (del) BaseT::useCount_ = nullptr_();
            }
        }

        inline BalWeakHandle& operator=(int Null) throw()
        {
            this->Clear(); return *this;
        }

        inline BalWeakHandle& operator=(const BalWeakHandle& handle) throw()
        {
            T* object = handle.object_;
            BalUseCount* count = handle.useCount_;
            count? count->AddUseCount(false) :(void)0; this->Clear();
            BaseT::object_ = object; BaseT::useCount_ = count;
            return *this;
        }

        template <typename U>
        inline BalWeakHandle& operator=(const BalWeakHandle<U>& handle) throw()
        {
            if (BaseT::HashCode() == handle.HashCode())
            {
                return *this;
            }

            this->Clear();
            BaseT::object_ = dynamic_cast<T*>(handle.GetBasePtr());
            if (nullptr_() != BaseT::object_)
            {
                BaseT::useCount_ = handle.useCount_;
                BaseT::useCount_?BaseT::useCount_->AddUseCount(false):(void)0;
            }
            return *this;
        }

        inline BalWeakHandle& operator=(const BalHandle<T>& handle) throw()
        {
            if (BaseT::HashCode() == handle.HashCode())
            {
                return *this;
            }

            this->Clear();
            BaseT::object_ = handle.object_;
            BaseT::useCount_ = handle.useCount_;
            BaseT::useCount_?BaseT::useCount_->AddUseCount(false):(void)0;
            return *this;
        }

        template <typename U>
        inline BalWeakHandle& operator=(const BalHandle<T>& handle) throw()
        {
            if (BaseT::HashCode() == handle.HashCode())
            {
                return *this;
            }

            this->Clear();
            BaseT::object_ = dynamic_cast<T*>(handle.GetBasePtr());
            if (nullptr_() != BaseT::object_)
            {
                BaseT::useCount_ = handle.useCount_;
                BaseT::useCount_?BaseT::useCount_->AddUseCount(false):(void)0;
            }
            return *this;
        }
    };
}
#endif
