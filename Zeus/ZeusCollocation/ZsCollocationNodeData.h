#ifndef Zeus_ZeusCollocation_ZsCollocationNodeData_H
#define Zeus_ZeusCollocation_ZsCollocationNodeData_H
#include <Zeus/ZeusBase/ZsNodeTree.h>
#include <Zeus/ZeusBase/ZsClientProtocol.h>
#include <Zeus/ZeusBase/ZsClientData.h>

namespace Zeus
{
    class ZsCollocationNodeData: public ZsNodeTree
    {
    public:
        bool AddServiceAddr(std::string service, std::string addr);
        bool DeleteServiceAddr(std::string service, std::string addr);
        std::string DumpNodeTreeData();

    private:
        bool DumpNodeTreeData(ZsNode* node, ZsClientData& data, std::string tag);

    private:
        std::string dataBuffer_;
    };
}
#endif
