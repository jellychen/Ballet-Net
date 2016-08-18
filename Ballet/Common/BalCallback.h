#ifndef Ballet_Common_BalCallback_H
#define Ballet_Common_BalCallback_H
#include "BalCoable.h"
#include "BalHandleInct.h"

namespace Ballet
{
    class BalCallback :public BalNoCoable
    {
    public:
        virtual bool IsCallable() const = 0;
    };
}

#define BalCallbackSinkBegin(SinkName)                                          \
template <typename Host, typename Sink> class SinkName: public Sink             \
{                                                                               \
public:                                                                         \
    Host* host_;
#define BalCallbackSinkComplete()                                               \
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
    SinkName##Ptr(const Host* host):sinkObject_(new CallbackSinkT())            \
    {                                                                           \
        if (!host)                                                              \
        {                                                                       \
            throw std::runtime_error("SinkPtr Construct Arguments!");           \
        }                                                                       \
        CallbackSinkT* sink = sinkObject_.GetBasePtr();                         \
        if (sink) sink->host_ = (Host*)host;                                    \
    }                                                                           \
    virtual ~SinkName##Ptr()                                                    \
    {                                                                           \
        CallbackSinkT* sink = sinkObject_.GetBasePtr();                         \
        if (sink) sink->host_ = nullptr_();                                     \
    }                                                                           \
    operator bool() const throw()                                               \
    {                                                                           \
        return sinkObject_.GetBasePtr();                                        \
    }                                                                           \
    inline CallbackSinkT* operator-> () const                                   \
    {                                                                           \
        return sinkObject_.GetBasePtr();                                        \
    }                                                                           \
    BalHandle<Sink> GetHandle() const                                           \
    {                                                                           \
        Sink* object = dynamic_cast<Sink*>(sinkObject_.GetBasePtr());           \
        return BalHandle<Sink>(sinkObject_, object);                            \
    }                                                                           \
private:                                                                        \
    BalHandle<CallbackSinkT> sinkObject_;                                       \
};
#endif
