#ifndef Libs_IniLoader_IniConfigLoader_H
#define Libs_IniLoader_IniConfigLoader_H
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
#endif
