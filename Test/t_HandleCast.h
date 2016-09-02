
#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalHandle.h>
using namespace Ballet;

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class t_HandleClass_class_base
{
public:
    t_HandleClass_class_base()
    {
        cout<<"t_HandleClass_class_base"<<endl;
    }

    virtual ~t_HandleClass_class_base()
    {
        cout<<"~t_HandleClass_class_base"<<endl;
    }

    virtual void test()
    {
        cout<<"test"<<endl;
    }
};

class t_HandleClass_class_inhreit:public t_HandleClass_class_base
{
public:
    t_HandleClass_class_inhreit()
    {
        cout<<"t_HandleClass_class_inhreit"<<endl;
    }

    virtual ~t_HandleClass_class_inhreit()
    {
        cout<<"~t_HandleClass_class_inhreit"<<endl;
    }

    virtual void test()
    {
        cout<<"test1"<<endl;
    }
};

void t_HandleCast_main()
{
    BalWeakHandle<t_HandleClass_class_inhreit> weak;
    {
        BalHandle<t_HandleClass_class_inhreit> objectInhert(new t_HandleClass_class_inhreit);
        BalHandle<t_HandleClass_class_base> objectBase
        = dynamic_cast_<t_HandleClass_class_inhreit, t_HandleClass_class_base>(objectInhert);
        if (objectBase)
        {
            objectBase->test();
        }
        weak = objectInhert;
        if (weak) weak->test();
    }
    if (weak) weak->test();
}
