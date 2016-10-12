#include "ZsNodeTree.h"
using namespace std;
using namespace Zeus;

ZsNodeTree::ZsNodeTree()
{

}

ZsNodeTree::~ZsNodeTree()
{

}

bool ZsNodeTree::Clear()
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
    children_.clear();
    return true;
}

std::string ZsNodeTree::RandomSelect(std::string service)
{
    ZsNode* node = GetPathNode(service, false);
    if (node)
    {
        return node->RandomSelect();
    }
    return "0.0.0.0:0";
}

bool ZsNodeTree::AddServiceAddr(std::string service, std::string addr)
{
    if (0 == service.length() || 0 == addr.length()) return false;
    ZsNode* node = GetPathNode(service, true);

    if (node)
    {
        return node->AddServiceAddr(addr);
    }
    return false;
}

bool ZsNodeTree::DeleteServiceAddr(std::string service, std::string addr)
{
    if (0 == service.length() || 0 == addr.length()) return false;
    ZsNode* node = GetPathNode(service, false);

    if (node)
    {
        return node->DeleteServiceAddr(addr);
    }
    return false;
}

bool ZsNodeTree::IsServerAddExist(std::string service, std::string addr)
{
    if (0 == service.length() || 0 == addr.length()) return false;
    ZsNode* node = GetPathNode(service, false);

    if (node)
    {
        return node->IsServerAddExist(addr);
    }
    return false;
}

ZsNode* ZsNodeTree::GetPathNode(std::string service, bool create)
{
    if (0 == service.length() || '/' != service[0]) return 0;
    int cur = 1; ZsNode* node = this; std::string nodeName = "";
    for (; cur < service.length(); ++cur)
    {
        char bit = service[cur];
        if ('/' != bit) nodeName += bit;
        if ('/' == bit || cur == service.length() -1)
        {
            if (0 == nodeName.length()) return false;
            ZsNodeChildrenT::iterator iter = node->children_.find(nodeName);
            if (node->children_.end() == iter)
            {
                if (create)
                {
                    ZsNode* temp = new ZsNode();
                    node->children_[nodeName] = temp;
                    node = temp;
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                node = iter->second;
            }
            nodeName.clear();
        }
    }
    return node;
}
