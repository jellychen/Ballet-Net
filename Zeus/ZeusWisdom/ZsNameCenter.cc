#include "ZsNameCenter.h"
using namespace Zeus;

bool ZsNameCenter::AddService(std::string name, std::string addr, uint32_t weight)
{
    if (name.empty() || addr.empty()) return false;

    BalHandle<ZsNameDefine> nameNode;
    mapNamePoolT::iterator iter = nameNamePool_.find(name);
    if (iter == nameNamePool_.end())
    {
        BalHandle<ZsNameDefine> nameNodeTemp(new ZsNameDefine);
        nameNode = nameNodeTemp;
        nameNamePool_[name] = nameNode;
    }
    else
    {
        nameNode = iter->second;
    }

    if (!nameNode)
    {
        return false;
    }

    nameNode->name_ = name;
    return nameNode->AddService(addr, weight);
}

bool ZsNameCenter::RemoveService(std::string name, std::string addr)
{
    if (name.empty() || addr.empty()) return false;

    BalHandle<ZsNameDefine> nameNode;
    mapNamePoolT::iterator iter = nameNamePool_.find(name);
    if (iter == nameNamePool_.end()) return false;
    nameNode = iter->second;
    if (!nameNode) return false;
    bool ret =  nameNode->RemoveService(addr);
    if (true == ret && 0 == nameNode->services_.size())
    {
        nameNamePool_.erase(iter);
    }
    return ret;
}

bool ZsNameCenter::DumpInfoFile(const char* file)
{
    if (nullptr_() == file)
    {
        return false;
    }

    std::string abslouteFile = workDir_ + file;
    if (::access(abslouteFile.c_str(), F_OK) != -1
            && 0 != ::unlink(abslouteFile.c_str()))
    {
        return false;
    }

    FILE* ioHandle = ::fopen(abslouteFile.c_str(), "w+");
    mapNamePoolT::iterator iter = nameNamePool_.begin();
    for (; iter != nameNamePool_.end(); ++iter)
    {
        BalHandle<ZsNameDefine> nameNode = iter->second;
        if (nameNode)
        {
            fprintf(ioHandle, "%s\t", nameNode->name_.c_str());
            std::vector<ZsNameService>& service = nameNode->services_;
            for (size_t i = 0; i < service.size(); ++i)
            {
                const char* buffer = service[i].serverAddr_.c_str();
                unsigned long weight = (unsigned long)service[i].weight_;
                fprintf(ioHandle, "%s,%lu;", buffer, weight);
            }
            fprintf(ioHandle, "#");
        }
    }

    if (0 != ::fflush(ioHandle)) return false;
    ::fclose(ioHandle);
    return true;
}
