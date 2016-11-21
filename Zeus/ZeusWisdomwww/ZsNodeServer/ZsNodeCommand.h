#ifndef Zeus_ZeusCollocation_ZsNodeServer_ZsNodeCommand_H
#define Zeus_ZeusCollocation_ZsNodeServer_ZsNodeCommand_H

namespace Zeus
{
    enum ZsNodeCommand
    {
        ZsNcVoteRequest         = 0,
        ZsNcVoteRespond         = 1,
        ZsNcAddEntriesRequest   = 2,
        ZsNcAddEntriesRespond   = 3,
    };
}
#endif
