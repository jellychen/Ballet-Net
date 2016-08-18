#ifndef Ballet_Common_BalHandle_H
#define Ballet_Common_BalHandle_H
#include "BalHandleBase.h"

namespace Ballet
{
    template<typename T> class BalWeakHandle;
    template<typename T> class BalHandle :public BalHandleBase<T>
    {
        friend class BalWeakHandle<T>;
        typedef BalHandleBase<T> BaseT;
    public:
        BalHandle() throw():BalHandleBase<T>()
        {
        }

        explicit BalHandle(T* object):BalHandleBase<T>()
        {
            if (nullptr_() == object) return;
            typedef BalUseCountWrapper<T> U;
            BaseT::useCount_ = new(std::nothrow)U(object);
            if (nullptr_() != BaseT::useCount_)
            {
                BaseT::object_ = object; return;
            }
            throw std::runtime_error("BalHandle Construct Failed");
        }

        template<typename U>
        explicit BalHandle(T* object):BalHandleBase<T>()
        {
            if (nullptr_() == object) return;
            BaseT::useCount_ = new(std::nothrow)U(object);
            if (nullptr_() != BaseT::useCount_)
            {
                BaseT::object_ = object; return;
            }
            throw std::runtime_error("BalHandle Construct Failed");
        }

        BalHandle(const BalHandle& handle) throw()
        {
            BaseT::object_ = handle.object_;
            BaseT::useCount_ = handle.useCount_;
            BaseT::useCount_?BaseT::useCount_->AddUseCount(true):(void)0;
        }

        BalHandle(const BalWeakHandle<T>& handle) throw()
        {
            BaseT::object_ = handle.object_;
            BaseT::useCount_ = handle.useCount_;
            BaseT::useCount_?BaseT::useCount_->AddUseCount(true):(void)0;
        }

        inline ~BalHandle()
        {
            this->Clear();
        }

    public:
        inline void Clear() throw()
        {
            if (nullptr_() != BaseT::object_ && nullptr_() != BaseT::useCount_)
            {
                bool del = false;
                BaseT::useCount_->DelUseCount(true, del);
                if (del) BaseT::useCount_ = nullptr_();
            }
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
    };
}
#endif
