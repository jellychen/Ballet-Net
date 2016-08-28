
#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalHandle.h>
using namespace Ballet;

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class t_Singleton_class:public BalShareThis
{
public:
    t_Singleton_class()
    {
        std::cout << "init" << std::endl;
    }

    virtual ~t_Singleton_class()
    {
        std::cout << "uninit" << std::endl;
    }

    void Get()
    {
        std::cout << "t_Singleton_class::Get" << std::endl;
    }
};

void t_Singleton_main()
{
    BalHandle<t_Singleton_class> instance = BalSingleton<t_Singleton_class>::GetInstance();
    instance->Get();
    BalHandle<t_Singleton_class> instance2 = BalSingleton<t_Singleton_class>::GetInstance();
    instance->Get();

}
