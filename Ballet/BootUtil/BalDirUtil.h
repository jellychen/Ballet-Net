#ifndef Ballet_BootUtil_BalDirUtil_H
#define Ballet_BootUtil_BalDirUtil_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace BootUtil
    {
        class BalDirUtil
        {
        public:
            static bool CreateDir(const char* path);

            static bool IsPathExist(const char* path);
        };
    }
}
#endif
