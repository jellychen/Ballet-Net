#ifndef Ballet_BootUtil_BalStringUtil_H
#define Ballet_BootUtil_BalStringUtil_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace BootUtil
    {
        inline void StrTrim(std::string& str)
        {
            if (str.length() > 0)
            {
                int end = str.find_last_not_of(" ");
                int start = str.find_first_not_of(" ");
                str = str.substr(start, end - start + 1);
            }
        }
    }
}
#endif
