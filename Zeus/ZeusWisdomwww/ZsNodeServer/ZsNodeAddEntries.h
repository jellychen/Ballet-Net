#ifndef Zeus_ZeusCollocation_ZsNodeServer_ZsNodeAddEntries_H
#define Zeus_ZeusCollocation_ZsNodeServer_ZsNodeAddEntries_H
#include <Ballet/Common/BalInct.h>
#include <Libs/MessagePack/MsgPackInct.h>
using namespace Ballet;

namespace Zeus
{
    enum ZsEntriesOpertaion
    {
        ZsEoNop         = 0,
        ZsEoPut         = 1,
        ZsEoDel         = 2,
        ZsEoLock        = 3,
        ZsEoUnLock      = 4,
    };

    struct ZsEntries
    {
        uint8_t opet_;
        std::string key_, value_;
        MSGPACK_DEFINE(opet_, key_, value_);
    };

    struct ZsAddEntriesRequest
    {
        std::string leaderId_;
        uint64_t term_, leaderCommit_;
        std::vector<ZsEntries> entries_;
        uint64_t prevLogIndex_, prevLogTerm_;
        MSGPACK_DEFINE(leaderId_, term_, leaderCommit_,\
                    entries_, prevLogIndex_, prevLogTerm_);
    };

    struct ZsAddEntriesRespond
    {
        bool success_; uint64_t term_;
        MSGPACK_DEFINE(success_, term_);
    };
}
#endif
