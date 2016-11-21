#include "BalDirUtil.h"
using namespace Ballet;
using namespace BootUtil;

bool BalDirUtil::CreateDir(const char* path)
{
    if (!path) return false;

    const int mode = S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH;
    size_t len = 0; char pathBuf[1024];
    snprintf(pathBuf, sizeof(pathBuf), "%s", path);
    len = strlen(path);

    if(pathBuf[len -1] == '/') pathBuf[len -1] = 0;
    for(char* current = pathBuf + 1; *current; current++)
    {
        if(*current == '/')
        {
            *current = 0;
            if (0 != ::mkdir(pathBuf, mode) && errno != EEXIST)
            {
                return false;
            }
            *current = '/';
        }
    }
    return  !(0 != ::mkdir(pathBuf, mode) && errno != EEXIST);
}


bool BalDirUtil::IsPathExist(const char* path)
{
    if (!path) return false;
    return 0 == ::access(path, F_OK);
}

std::string BalDirUtil::AbsolutePath(const char* path)
{
    char resolvedPath[1024] = {0};
    ::realpath(path, resolvedPath);
    return std::string(resolvedPath);
}

std::string BalDirUtil::CombinePath(const char* a, const char* b)
{
    std::string path(a); path += b;
    return BalDirUtil::AbsolutePath(path.c_str());
}
