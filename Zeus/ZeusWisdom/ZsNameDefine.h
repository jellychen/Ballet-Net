#ifndef Zeus_ZeusWisdom_ZsNameDefine_H
#define Zeus_ZeusWisdom_ZsNameDefine_H
#include <Ballet/Common/BalInct.h>
using namespace Ballet;

namespace Zeus
{
    class ZsNameService
    {
    public:
        ZsNameService(const char* addr, uint32_t weight)
        {
            serverAddr_ = addr; weight_ = weight;
        }

    public:
        uint32_t weight_; // 0 for debug
        std::string serverAddr_;
    };


    class ZsNameDefine
    {
    public:
        ZsNameDefine();

    public:
        bool AddService(std::string& addr, uint32_t weight);
        bool RemoveService(std::string& addr);

    public:
        std::string name_;
        std::vector<ZsNameService> services_;
    };
}
#endif
