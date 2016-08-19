#ifndef Ballet_Common_BalUseCount_H
#define Ballet_Common_BalUseCount_H
#include "BalInct.h"
#include "BalNull.h"
#include "BalCoable.h"

namespace Ballet
{
    class BalUseCount :public BalNoCoable
    {
    public:
        BalUseCount():useCount_(1),weakUseCount_(0)
        {
        }

    public:
        long UseCount() const
        {
            return useCount_ + weakUseCount_;
        }

        bool IsAlived() const
        {
            return useCount_ > 0;
        }

    public:
        virtual long HashCode() const = 0;
        virtual void AddUseCount(bool ref) = 0;
        virtual void DelUseCount(bool ref, bool& del) = 0;

    public:
        long useCount_, weakUseCount_;
    };

    template<typename T>class BalUseCountWrapper :public BalUseCount
    {
    public:
        BalUseCountWrapper(T* object):BalUseCount()
        {
            object_ = object;
        }

        virtual long HashCode() const
        {
            return (long)(object_);
        }

        virtual void AddUseCount(bool ref)
        {
            if (true == ref)
            {
                ++useCount_;
            }
            else
            {
                ++weakUseCount_;
            }
        }

        virtual void DelUseCount(bool ref, bool& del)
        {
            if (true == ref)
            {
                --useCount_;
                if (0 == useCount_)
                {
                    this->_Destory();
                }
            }
            else
            {
                --weakUseCount_;
            }

            if (0 == (useCount_ + weakUseCount_))
            {
                del = true; delete this;
            }
        }

        virtual void _Destory()
        {
            if (nullptr_() != object_)
            {
                delete object_;
                object_ = nullptr_();
            }
        }
    protected:
        T* object_;
    };
}
#endif
