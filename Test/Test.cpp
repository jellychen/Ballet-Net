#include <iostream>
using namespace std;
#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalBase.h>
#include <Ballet/Common/BalSharePtr.h>
#include <Ballet/Common/BalWeakPtr.h>

using namespace Ballet;
using namespace Common;
class A
{
public:
    A()
    {
        cout<<"A"<<endl;
    }

    ~A()
    {
        cout<<"~A"<<endl;
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

    set();


    return 0;
}
