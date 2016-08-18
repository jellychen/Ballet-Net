#include <Ballet/Common/BalInct.h>
using namespace Ballet;

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class ICallback :public BalCallback
{
public:
    virtual void Get() = 0;
};


BalCallbackSinkBegin(CCallback)
BalCallbackSink(void, Get, (), ())
BalCallbackSinkComplete()
BalCallbackSinkPtrDefine(CCallback, ICallback)

class t_Callback_class
{
public:
    t_Callback_class():callbackPtr(this)
    {
        if (callbackPtr)
        {
            callbackPtr->HookGet(&t_Callback_class::GetCallback);
        }
    }
    ~t_Callback_class()
    {
        std::cout << "/* message */" << std::endl;
    }

    void GetCallback()
    {
        std::cout << "GetCallback" << std::endl;
    }

    CCallbackPtr<t_Callback_class> callbackPtr;
};


void t_Callback_main()
{
    std::cout << "t_Callback_main" << std::endl;
    BalHandle<ICallback> callback;
    {
        t_Callback_class instance;
        callback = instance.callbackPtr.GetHandle();
    }

    if (callback->IsCallable())
    {
        callback->Get();
    }
}
