#include <map>
#include <string>

namespace Libs
{
    class IniConfigLoader
    {
    public:
        bool LoadFile(const char*) const;
        bool GetItem(const char*, std::string*, const char*) const;

    private:
        typedef std::map<std::string, std::string> mapPoolT;
        mapPoolT configItemPool_;
    };
}
