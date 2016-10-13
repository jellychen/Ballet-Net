#ifndef Zeus_ZeusBroker_ZsNode_H
#define Zeus_ZeusBroker_ZsNode_H
#include <map>
#include <vector>
#include <string>

namespace Zeus
{
    class ZsNode;
    typedef std::map<std::string, ZsNode*> ZsNodeChildrenT;
    typedef std::vector<std::string> ZsNodeServicePoolT;

    class ZsNode
    {
    public:
        ZsNode();
        virtual ~ZsNode();

    public:
        std::string RandomSelect();
        bool AddServiceAddr(std::string addr);
        bool DeleteServiceAddr(std::string addr);
        bool IsServerAddExist(std::string addr);

    public:
        ZsNodeChildrenT children_;
        ZsNodeServicePoolT servicePool_;
    };
}
#endif
