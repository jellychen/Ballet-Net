#include <Ballet/Common/BalInct.h>
using namespace Ballet;

#include <iostream>
#include <memory>
#include <vector>
#include <map>
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

    virtual void GetCallback(int i)
    {
        std::cout << "GetCallback" << std::endl;
    }

    CCallbackPtr<t_Callback_class> callbackPtr;
};

class t_Callback_class_2 :public t_Callback_class
{
public:
    int sadata;
    virtual void GetCallback(int i)
    {
        std::cout << "GetCallback3" << std::endl;
    }

};

struct wrraper
{
    BalHandle<ICallback> callback;
};

void t_Callback_main()
{
    typedef std::map<int, wrraper > t_map;
    t_map _map;

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

        wrraper ss = {callback};
        _map[0] = ss;
    }
    cout<<__LINE__<<endl;
    t_map::iterator iter = _map.find(0);
    _map.erase(iter);
}
