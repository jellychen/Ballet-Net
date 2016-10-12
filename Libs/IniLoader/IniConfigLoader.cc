#include <sstream>
#include <fstream>
using namespace std;

#include "IniConfigLoader.h"
using namespace Libs;

bool IniConfigLoader::LoadFile(const char* file) const
{
    if (!file) return false;
    std::ifstream fin(file, std::ios::in);
    if (!fin.good()) return false;

    const int lineLen = 1024;
    char line[lineLen] = {0};
    while (fin.getline(line, lineLen))
    {
        int start = 0;
        for (; start < lineLen; ++start)
        {
            if (' ' != line[start]) break;
        }
        if (start < lineLen && '#' == line[start]) break;

        std::string key = "";
        for (; start < lineLen; ++start)
        {
            char bit = line[start];
            if (' ' == bit || '=' == bit) break;
            key += bit;
        }
        if (0 == key.length()) break;

        for (; start < lineLen; ++start)
        {
            char bit = line[start];
            if (' ' != bit && '=' != bit) break;
        }

        std::string value = "";
        for (; start < lineLen; ++start)
        {
            char bit = line[start];
            if (' ' == bit) break;
            value += bit;
        }
        if (0 == value.length()) break;

        printf("%s:%s\n", key.c_str(), value.c_str());
    }
    fin.clear(); fin.close();
    return true;
}

bool IniConfigLoader::GetItem(const char* key, std::string* value, const char* defaultValue) const
{
    if (!key || !value) return false;
    std::string keyValue = key;
    std::string valueItem = defaultValue;
    mapPoolT::const_iterator iter = configItemPool_.find(keyValue);
    if (configItemPool_.end() != iter)
    {
        valueItem = iter->second;
    }
    *value = valueItem;
    return true;
}
