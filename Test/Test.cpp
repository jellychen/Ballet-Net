#include <iostream>
using namespace std;
#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalBase.h>

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
};

int main(int argc, char const *argv[])
{
    Ballet::Common::BalBaseImplement<A>* object = NULL;
    object = Ballet::Common::BalBaseImplement<A>::CreateInstance();
    object->ownerShip_->Release();
    return 0;
}
