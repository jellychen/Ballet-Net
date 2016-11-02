#ifndef Zeus_ZeusCollocation_ZsWorkboard_ZsWorkboard_H
#define Zeus_ZeusCollocation_ZsWorkboard_ZsWorkboard_H
#include <Ballet/Common/BalInct.h>
#include <Ballet/BootUtil/BalDirUtil.h>
#include <Ballet/BootUtil/BalMutexWatcher.h>
using namespace Ballet;
using namespace BootUtil;

#include "ZsWorkboardOptions.h"

namespace Zeus
{
    class ZsWorkboard: public BalNoCoable
    {
    public:
        ZsWorkboard(const char*);
        virtual ~ZsWorkboard();

    public:
        bool IsProcessExist(int*);
        bool WriteProcessIdIntoFile();

    private:
        std::string workboard_;
        ZsWorkboardOptions opts_;
    };
}
#endif
