#ifndef Ballet_BootUtil_BalGuid_H
#define Ballet_BootUtil_BalGuid_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace BootUtil
    {
        inline void BalGuidRandom(std::string& str)
        {
            char buffer[37] = {0};
            const char* c = "89ab"; char* p = buffer;
            for (int n = 0; n < 16; ++n)
            {
                int b = rand() %255;
                switch (n)
                {
                    case 6:
                        sprintf(p, "4%x", b%15);
                        break;
                    case 8:
                        sprintf(p, "%c%x", c[rand() %strlen(c)], b%15);
                        break;
                    default:
                        sprintf(p, "%02x", b);
                        break;
                }

                p += 2;
                switch (n)
                {
                    case 3: case 5: case 7: case 9:
                        *p++ = '-';
                        break;
                }
            }
            *p = 0; str = buffer;
        }
    }
}
#endif
