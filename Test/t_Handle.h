
#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalHandle.h>
using namespace Ballet;

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class t_Handle_class
{
public:
    t_Handle_class()
    {
        cout<<"t_Handle_class"<<endl;
    }

    virtual ~t_Handle_class()
    {
        cout<<"~t_Handle_class"<<endl;
    }

    void test()
    {
        cout<<"test"<<endl;
    }
};

void t_Handle_main()
{
    // note: 1
    {
        BalHandle<t_Handle_class> classPtr(new t_Handle_class);
    }
    std::cout << "" << std::endl;

    // note: 2
    {
        typedef std::vector<BalHandle<t_Handle_class> > t_vec;
        t_vec _vec;
        {
            BalHandle<t_Handle_class> classPtr(new t_Handle_class);
            _vec.push_back(classPtr);
            cout<<__LINE__<<endl;
        }
        cout<<__LINE__<<endl;
    }
    std::cout << "" << std::endl;

    // note: 3
    {

    }
    std::cout << "" << std::endl;
}
