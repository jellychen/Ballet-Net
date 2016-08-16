#ifndef Ballet_Common_BalCallback_H
#define Ballet_Common_BalCallback_H
#include "BalSharePtr.h"

namespace Ballet
{
    namespace Common
    {
        class BalCallback
        {
        public:
            virtual bool IsCallable() = 0;
        };
    }
}

#define BalCallbackSinkBegin(SinkName)                                          \
template <typename Host, typename Sink> class SinkName: public Sink             \
{                                                                               \
public:                                                                         \
    Host* host_;                                                                \
#define BalCallbackSinkComplete                                                 \
public:                                                                         \
    bool IsCallable() const                                                     \
    {                                                                           \
        return this->host_;                                                     \
    }                                                                           \
};

template<typename T> struct BalCallbackSinkWrapper
{
    T data_;
    BalCallbackSinkWrapper():data_(0)
    {
    }
};

#define BalCallbackSink(Ret, Name, Param, Args)                                 \
public:                                                                         \
    typedef Ret(Host::*__pf##Name) Param;                                       \
    BalCallbackSinkWrapper<__pf##Name> __pf##Name##_function;                   \
    void Hook##Name(__pf##Name func)                                            \
    {                                                                           \
        __pf##Name##_function.data_ = func;                                     \
    }                                                                           \
    void UnHook##Name()                                                         \
    {                                                                           \
        __pf##Name##_function.data_ = (__pf##Name)(0);                          \
    }                                                                           \
    Ret Name Param                                                              \
    {                                                                           \
        if (0 == __pf##Name##_function.data_)                                   \
        {                                                                       \
            return (Ret)(0);                                                    \
        }                                                                       \
        return (this->host_->*(__pf##Name##_function.data_)) Param;             \
    }

#define BalCallbackSinkPtrDefine(SinkName, Sink)                                \
template<typename Host> class SinkName##Ptr                                     \
{                                                                               \
    typedef SinkName<Host, Sink> CallbackSinkT;                                 \
public:                                                                         \
    SinkName##Ptr(const Host* host)                                             \
    {                                                                           \                                                                        \
    }                                                                           \
    virtual ~SinkName##Ptr()                                                    \
    {                                                                           \
    }                                                                           \
private:                                                                        \
    
}
#endif
