#ifndef Zeus_ZeusCollocation_ZsWorkboard_ZsWorkboardOptions_H
#define Zeus_ZeusCollocation_ZsWorkboard_ZsWorkboardOptions_H
#include <Ballet/Common/BalInct.h>
#include <Ballet/BootUtil/BalStringUtil.h>
#include <Libs/RapidXml/rapidxml.hpp>
using namespace Ballet;
using namespace BootUtil;

namespace Zeus
{
    class ZsWorkboardOptions: public BalNoCoable
    {
    public:
        ZsWorkboardOptions();

    public:
        void LoadOptions(const char*);

    public:
        uint32_t RandomVoteElectionTimeout() const;

    public:
        bool netIpv6_;
        uint16_t netListenPort_;
        uint32_t maxTimeout_;
        uint32_t maxPackageSize_;
        uint32_t maxReadBufferSize_;
        uint32_t maxWriteBufferSize_;
        uint32_t maxHeartbeatTimeout_;
        uint32_t minVoteElectionTimeout_;
        uint32_t maxVoteElectionTimeout_;
        std::vector<std::string> consistentGroup_;
    };
}
#endif
