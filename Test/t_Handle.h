
#include <Ballet/Common/BalInct.h>
#include <Ballet/Common/BalNull.h>
#include <Ballet/Common/BalHandle.h>
using namespace Ballet;

#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <map>
using namespace std;

#include "shared_ptr.hpp"


class t_Handle_class_base
{
public:
    virtual ~t_Handle_class_base()
    {
        cout<<"~t_Handle_class_base"<<endl;
    }
};

class t_Handle_class :public t_Handle_class_base
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


void get(BalHandle<t_Handle_class>)
{

}

void t_Handle_main()
{
    // note: 1

    /*
    {
        BalHandle<t_Handle_class> classPtr(new t_Handle_class);
    }
    std::cout << "start" << std::endl;

    std::cout << "vec" << std::endl;
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
    std::cout << "~vec" << std::endl;

    // note: 3
    std::cout << "list" << std::endl;
    {
        typedef std::list<BalHandle<t_Handle_class> > t_list;
        t_list _list;
        {
            BalHandle<t_Handle_class> classPtr(new t_Handle_class);
            _list.push_back(classPtr);
            BalHandle<t_Handle_class> classPtr1(new t_Handle_class);
            _list.push_back(classPtr1);
            cout<<__LINE__<<endl;
        }
        cout<<__LINE__<<endl;
    }
    std::cout << "~list" << std::endl;

    // note: 4
    std::cout << "map" << std::endl;
    {
        typedef std::map<int, BalHandle<t_Handle_class> > t_map;
        t_map _map;
        {
            BalHandle<t_Handle_class> classPtr(new t_Handle_class);
            _map[0] = classPtr;
            BalHandle<t_Handle_class> classPtr1(new t_Handle_class);
            _map[0] = classPtr;
            cout<<__LINE__<<endl;
        }
        cout<<__LINE__<<endl;
    }
    std::cout << "~map" << std::endl;
    */

    // note: 4
    std::cout << "cast" << std::endl;
    {
        typedef std::map<int, BalHandle<t_Handle_class_base> > t_map;
        t_map _map;
        {
            BalHandle<t_Handle_class> ptr(new t_Handle_class);
            _map[0] = ptr;
            cout<<__LINE__<<endl;

            t_map::iterator iter = _map.find(0);
            _map.erase(iter);
        }
        cout<<__LINE__<<endl;
        //get(ptr);

    }
    std::cout << "~cast" << std::endl;

/*
    typedef std::map<int, shared_ptr<t_Handle_class> > t_map_s;
    t_map_s _map;
    shared_ptr<t_Handle_class_base> ptr(new t_Handle_class_base());
    _map[0] = ptr;
*/
}
