#ifndef Zeus_ZeusBroker_ZsNodeTree_H
#define Zeus_ZeusBroker_ZsNodeTree_H
#include "ZsNode.h"

namespace Zeus
{
    class ZsNodeTree: public ZsNode
    {
    public:
        ZsNodeTree();
        virtual ~ZsNodeTree();

    public:
        bool Clear();
        std::string RandomSelect(std::string service);
        bool AddServiceAddr(std::string service, std::string addr);
        bool DeleteServiceAddr(std::string service, std::string addr);
        bool IsServerAddExist(std::string service, std::string addr);
        bool GetHeadNode(std::string& tag, ZsNode** node);

    private:
        ZsNode* GetPathNode(std::string service, bool create);

    };
}
#endif
