#ifndef Ballet_Common_BalHandle_H
#define Ballet_Common_BalHandle_H
#include "BalHandleBase.h"

namespace Ballet
{
    template<typename T> class BalWeakHandle;
    template<typename T> class BalHandle :public BalHandleBase<T>
    {
        template<typename U>
        friend class BalHandle;
        friend class BalWeakHandle<T>;
        typedef BalHandleBase<T> BaseT;
    public:
        BalHandle() throw()
        {
        }

        explicit BalHandle(T* object)
        {
            if (nullptr_() == object) return;
            typedef BalUseCountWrapper<T> U;
            BaseT::useCount_ = new(std::nothrow)U(object);
            if (nullptr_() != BaseT::useCount_)
            {
                BaseT::object_ = object;
                BalHandle::__InternalUseCount(object, BaseT::useCount_);
                return;
            }
            throw std::runtime_error("BalHandle Construct Failed");
        }

        explicit BalHandle(T* object, BalUseCount* count)
        {
            if (nullptr_() == object) return;
            if (nullptr_() != count)
            {
                BaseT::object_ = object;
                BaseT::useCount_ = count;
                BaseT::useCount_?BaseT::useCount_->AddUseCount(true):(void)0;
                return;
            }
            throw std::runtime_error("BalHandle Construct Failed");
        }

        template<typename U>
        explicit BalHandle(const BalHandle<U>& handle, T* object)
        {
            if (nullptr_() == object) return;
            BaseT::object_ = object;
            BaseT::useCount_ = handle.useCount_;
            BaseT::useCount_?BaseT::useCount_->AddUseCount(true):(void)0;
        }

        template<typename U> explicit BalHandle(T* object)
        {
            if (nullptr_() == object) return;
            BaseT::useCount_ = new(std::nothrow)U(object);
            if (nullptr_() != BaseT::useCount_)
            {
                BaseT::object_ = object; return;
            }
            throw std::runtime_error("BalHandle Construct Failed");
        }

        BalHandle(const BalHandle<T>& handle) throw()
        {
            BaseT::object_ = handle.object_;
            BaseT::useCount_ = handle.useCount_;
            BaseT::useCount_?BaseT::useCount_->AddUseCount(true):(void)0;
        }

        template <typename U>
        explicit BalHandle(const BalHandle<U>& handle) throw()
        {
            if (!handle) return;
            BaseT::object_ = dynamic_cast<T*>(handle.GetBasePtr());
            if (nullptr_() != BaseT::object_)
            {
                BaseT::useCount_ = handle.useCount_;
                BaseT::useCount_?BaseT::useCount_->AddUseCount(true):(void)0;
            }
        }

        BalHandle(const BalWeakHandle<T>& handle) throw()
        {
            BaseT::object_ = handle.object_;
            BaseT::useCount_ = handle.useCount_;
            BaseT::useCount_?BaseT::useCount_->AddUseCount(true):(void)0;
        }

        template <typename U>
        BalHandle(const BalWeakHandle<U>& handle) throw()
        {
            if (!handle) return;
            BaseT::object_ = dynamic_cast<T*>(handle.GetBasePtr());
            if (nullptr_() != BaseT::object_)
            {
                BaseT::useCount_ = handle.useCount_;
                BaseT::useCount_?BaseT::useCount_->AddUseCount(true):(void)0;
            }
        }

        inline ~BalHandle()
        {
            this->Clear();
        }

    private:
        inline void __InternalUseCount(...) {}
        inline void __InternalUseCount(BalShareThis* shareThis, BalUseCount* count)
        {
            if (0 != shareThis && 0 != count)
            {
                shareThis->__InternalUseCount(count);
            }
        }

    public:
        inline void Clear() throw()
        {
            if (nullptr_() != BaseT::object_ && nullptr_() != BaseT::useCount_)
            {
                bool del = false;
                BaseT::useCount_->DelUseCount(true, del);
                BaseT::object_ = nullptr_(); BaseT::useCount_ = nullptr_();
            }
        }

        inline BalHandle& operator=(int Null) throw()
        {
            this->Clear(); return *this;
        }

        inline BalHandle& operator=(const BalHandle& handle) throw()
        {
            if (BaseT::HashCode() == handle.HashCode())
            {
                return *this;
            }

            this->Clear();
            BaseT::object_ = handle.object_;
            BaseT::useCount_ = handle.useCount_;
            BaseT::useCount_?BaseT::useCount_->AddUseCount(true):(void)0;
            return *this;
        }

        template <typename U>
        inline BalHandle& operator=(const BalHandle<U>& handle) throw()
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
                BaseT::useCount_?BaseT::useCount_->AddUseCount(true):(void)0;
            }
        }

        inline BalHandle& operator=(const BalWeakHandle<T>& handle) throw()
        {
            if (BaseT::HashCode() == handle.HashCode())
            {
                return *this;
            }

            this->Clear();
            BaseT::object_ = handle.object_;
            BaseT::useCount_ = handle.useCount_;
            BaseT::useCount_?BaseT::useCount_->AddUseCount(true):(void)0;
            return *this;
        }

        template <typename U>
        inline BalHandle& operator=(const BalWeakHandle<T>& handle) throw()
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
                BaseT::useCount_?BaseT::useCount_->AddUseCount(true):(void)0;
            }
        }
    };
}
#endif
