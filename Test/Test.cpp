#include <iostream>
using namespace std;
#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalBase.h>
#include <Ballet/Common/BalSharePtr.h>

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

int main(int argc, char const *argv[])
{
    //Ballet::Common::BalBaseImplement<A>* object = NULL;
    //object = Ballet::Common::BalBaseImplement<A>::CreateInstance();
    //object->ownerShip_->ReleaseMemory();
    Ballet::Common::BalSharePtr<A> ptr;
    ptr = Ballet::Common::BalBaseImplement<A>::CreateInstance();
    ptr->set();
    return 0;
}
