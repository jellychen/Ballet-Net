
#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalHandle.h>
using namespace Ballet;

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class t_ShareThis_class:public BalShareThis
{
public:
    t_ShareThis_class()
    {
        std::cout << "init" << std::endl;
    }

    virtual ~t_ShareThis_class()
    {
        std::cout << "uninit" << std::endl;
    }

    BalHandle<t_ShareThis_class> GetHandle()
    {
        BalHandle<t_ShareThis_class> ptr(this, shareUserCount_);
        return ptr;
    }
};

void t_ShareThis_main()
{
    BalHandle<t_ShareThis_class> ptr;
    {
        //t_ShareThis_class _d;
        //ptr = _d.GetHandle();

        BalHandle<t_ShareThis_class> __ptr(new t_ShareThis_class);
        ptr = __ptr->GetHandle();
        std::cout << "/* message */" << std::endl;
    }
}
