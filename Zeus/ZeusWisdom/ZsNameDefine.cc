#include "ZsNameDefine.h"
using namespace Zeus;

ZsNameDefine::ZsNameDefine()
{

}

bool ZsNameDefine::AddService(std::string& addr, uint32_t weight)
{
    if (addr.empty() || addr.length() > 512) return false;
    for (size_t i = 0; i < services_.size(); ++i)
    {
        if (addr == services_[i].serverAddr_)
        {
            if (services_[i].weight_ == weight)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    services_.push_back(ZsNameService(addr.c_str(), weight));
    return true;
}

bool ZsNameDefine::RemoveService(std::string& addr)
{
    if (addr.empty() || addr.length() > 512) return false;

    int index = -1;
    for (size_t i = 0; i < services_.size(); ++i)
    {
        if (addr == services_[i].serverAddr_)
        {
            index = (int)i; break;
        }
    }

    if (-1 == index) return false;

    services_.erase(services_.begin() + index);
    return true;
}
