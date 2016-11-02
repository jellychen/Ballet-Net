#ifndef Zeus_ZeusCollocation_ZsNodeServer_ZsNodeVote_H
#define Zeus_ZeusCollocation_ZsNodeServer_ZsNodeVote_H
#include <Ballet/Common/BalInct.h>
#include <Libs/MessagePack/MsgPackInct.h>
using namespace Ballet;

namespace Zeus
{
    struct ZsVoteRequest
    {
        std::string candidateId_;
        uint64_t term_, lastLogTerm_, lastLogIndex_;
        MSGPACK_DEFINE(term_, lastLogTerm_, lastLogIndex_, candidateId_);
    };

    struct ZsVoteRespond
    {
        uint64_t term_; bool voteGranted_;
        MSGPACK_DEFINE(term_, voteGranted_);
    };
}
#endif
