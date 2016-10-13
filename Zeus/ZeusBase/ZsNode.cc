#include <ctime>
#include <cstdlib>
#include "ZsNode.h"
using namespace std;
using namespace Zeus;

ZsNode::ZsNode()
{

}

ZsNode::~ZsNode()
{
    ZsNodeChildrenT::iterator iter = children_.begin();
    for (; iter != children_.end(); ++iter)
    {
        ZsNode* ptr = iter->second;

        if (ptr)
        {
            delete ptr;
        }
    }
}

std::string ZsNode::RandomSelect()
{
    if (0 == servicePool_.size())
    {
        return "0.0.0.0:0";
    }

    srand(unsigned(time(0)));
    int index = rand() %(servicePool_.size());
    return servicePool_[index];
}

bool ZsNode::AddServiceAddr(std::string addr)
{
    bool isIn = false;
    for (size_t i = 0; i < servicePool_.size(); ++i)
    {
        isIn = (servicePool_[i] == addr);
    }

    if (false == isIn)
    {
        servicePool_.push_back(addr);
    }
    return true;
}

bool ZsNode::DeleteServiceAddr(std::string addr)
{
    int index = -1;
    for (size_t i = 0; i < servicePool_.size(); ++i)
    {
        if (servicePool_[i] == addr)
        {
            index = (int)i; break;
        }
    }

    if (index > 0)
    {
        ZsNodeServicePoolT::iterator iter = servicePool_.begin() +index;
        servicePool_.erase(iter);
    }
    return true;
}

bool ZsNode::IsServerAddExist(std::string addr)
{
    bool isIn = false;
    for (size_t i = 0; i < servicePool_.size(); ++i)
    {
        isIn = (servicePool_[i] == addr);
    }
    return isIn;
}
