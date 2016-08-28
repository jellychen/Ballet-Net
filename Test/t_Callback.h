#include <Ballet/Common/BalInct.h>
using namespace Ballet;

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class ICallback :public BalCallback
{
public:
    virtual void Get(int i) = 0;
};


BalCallbackSinkBegin(CCallback)
BalCallbackSink(void, Get, (int i), (i))
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

     void GetCallback(int i)
    {
        std::cout << "GetCallback" << std::endl;
    }

    CCallbackPtr<t_Callback_class> callbackPtr;
};

class t_Callback_class_2 :public t_Callback_class
{
public:
    int sadata;
     void GetCallback(int i)
    {
        std::cout << "GetCallback3" << std::endl;
    }

};


void t_Callback_main()
{
    std::cout << "t_Callback_main" << std::endl;
    BalHandle<ICallback> callback;
    {
        t_Callback_class_2 instance;
        callback = instance.callbackPtr.GetHandle();
        callback->Get(10);
    }

    if (callback->IsCallable())
    {
        callback->Get(10);
    }
}
