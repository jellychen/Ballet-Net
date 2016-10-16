#include "ZsCollocationNodeData.h"
using namespace Zeus;

bool ZsCollocationNodeData::AddServiceAddr(std::string service, std::string addr)
{
    dataBuffer_.clear();
    return ZsNodeTree::AddServiceAddr(service, addr);
}

bool ZsCollocationNodeData::DeleteServiceAddr(std::string service, std::string addr)
{
    dataBuffer_.clear();
    return ZsNodeTree::DeleteServiceAddr(service, addr);
}

std::string ZsCollocationNodeData::DumpNodeTreeData()
{
    if (dataBuffer_.size() == 0)
    {
        ZsClientData nodeTreeData;
        nodeTreeData.type_ = ZsClientDataCreate;

        std::string headTag;
        ZsNode* headNode = nullptr_();
        if (GetHeadNode(headTag, &headNode))
        {
            DumpNodeTreeData(headNode, nodeTreeData, headTag);
            nodeTreeData.Serialize(dataBuffer_, false);
        }
    }
    return dataBuffer_;
}

bool ZsCollocationNodeData::DumpNodeTreeData(ZsNode* node, ZsClientData& data, std::string tag)
{
    if (!node) return false;
    ZsClientDataAddr dataAddr;
    dataAddr.name_.assign(tag.c_str());
    dataAddr.address_.resize(node->servicePool_.size());
    for (size_t i = 0; i < node->servicePool_.size(); ++i)
    {
        std::string& str = node->servicePool_.at(i);
        dataAddr.address_.at(i).assign(str.c_str());
    }
    data.array_.push_back(dataAddr);

    ZsNodeChildrenT::iterator iter = node->children_.begin();
    for (; iter != node->children_.end(); ++iter)
    {
        tag += iter->first;
        DumpNodeTreeData(iter->second, data, tag);
    }
    return true;
}
