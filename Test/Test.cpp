#include <iostream>
#include <memory>
using namespace std;
#include <vector>
#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalBase.h>
#include <Ballet/Common/BalSharePtr.h>
#include <Ballet/Common/BalWeakPtr.h>
#include <Ballet/Network/BalBuffer.h>

using namespace Ballet;
using namespace Common;
using namespace Network;

class A: public BalBase
{
public:
    A()
    {
        //cout<<"A"<<endl;
    }

    ~A()
    {
        //cout<<"~A"<<endl;
    }

    void set()
    {
        std::cout << "asdasdasdasd" << std::endl;
    }
};

class B
{
public:
    B()
    {
        //cout<<"A"<<endl;
    }

    ~B()
    {
        //cout<<"~A"<<endl;
    }

    void set()
    {
        std::cout << "asdasdasdasd" << std::endl;
    }
};

int get(BalSharePtr<A>& data)
{
    data->set();
    return 0;
}

BalSharePtr<A> set()
{
    BalSharePtr<A> ptr; ptr.NewInstance();
    return ptr;
}

int main(int argc, char const *argv[])
{
    //Ballet::Common::BalBaseImplement<A>* object = NULL;
    //object = Ballet::Common::BalBaseImplement<A>::CreateInstance();
    //object->ownerShip_->ReleaseMemory();
    for (int i =0; i < 100000000; ++i)
    {
        //A* s = BalBaseImplement<A>::CreateInstance();
        //s->ReleaseMemory();
        //BalSharePtr<A> ptr(BalBaseImplement<A>::CreateInstance());
        /*B* s = new B();
        delete s;*/
    }

    return 0;
}
