#ifndef Zeus_ZeusWisdom_ZsNameCenter_H
#define Zeus_ZeusWisdom_ZsNameCenter_H
#include <Ballet/Common/BalInct.h>
using namespace Ballet;

#include "ZsNameDefine.h"

namespace Zeus
{
    class ZsNameCenter
    {
        typedef std::map<std::string, BalHandle<ZsNameDefine> > mapNamePoolT;

    public:
        ZsNameCenter(const char* dir)
        {
            if (nullptr_() == dir)
            {
                throw std::runtime_error("ZsNameCenter Without WorkDir!");
            }
            workDir_ = dir;
        }

    public:
        bool AddService(std::string name, std::string addr, uint32_t weight);
        bool RemoveService(std::string name, std::string addr);
        bool DumpInfoFile(const char*);

    public:
        std::string workDir_;
        mapNamePoolT nameNamePool_;
    };
}
#endif
