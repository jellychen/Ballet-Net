#include "BalArpDef.h"
#include "BalArpBroadcast.h"
using namespace Ballet;
using namespace Protocol;

#define HARD_TYPE_ETHER     0x01    //硬件类型
#define PROTOCOL_IP         0x01    //IP协议类型
#define MAC_ADDR_LEN        0x06    //硬件地址长度
#define IP_ADDR_LEN         0x04    //IP地址长度
#define ARP_OP_REQUEST      0x01    //ARP请求操作
#define ARP_OP_RESPONSE     0x02    //ARP响应操作

BalArpBroadcast::BalArpBroadcast()
{
    fd_ = socket(AF_PACKET, SOCK_DGRAM, 0);
    if (fd_ <= 0)
    {
        throw std::runtime_error("BalArpAccord Construct Failed! @1");
    }
}

BalArpBroadcast::~BalArpBroadcast()
{
    if (0 != fd_)
    {
        ::close(fd_);
    }
}

bool BalArpBroadcast::Broadcast(std::string ip, std::string mac, int times) const
{
    if (times <= 0) return false;
    int macTemp[6] = {0};
    int len = sscanf(mac.c_str(), "%02x:%02x:%02x:%02x:%02x:%02x",
        &macTemp[0], &macTemp[1], &macTemp[2], &macTemp[3], &macTemp[4], &macTemp[5]);
    if (6 != len) return false;
    uint8_t macBinary[6] = {0};
    for (int i = 0; i < 6; ++i) macBinary[i] = (uint8_t)macTemp[i];

    int ipTemp[4] = {0};
    len = sscanf(ip.c_str(), "%d.%d.%d.%d",
        &ipTemp[0], &ipTemp[1], &ipTemp[2], &ipTemp[3]);
    if (4 != len) return false;
    uint8_t ipBinary[4] = {0};
    for (int i = 0; i < 4; ++i) ipBinary[i] = (uint8_t)ipTemp[i];
    return BroadcastBinary(ipBinary, macBinary, times);
}

bool BalArpBroadcast::BroadcastHardware(std::string ip, std::string ethernet, int times) const
{
    if (times <= 0) return false;
    int ipTemp[4] = {0};
    int len = sscanf(ip.c_str(), "%d.%d.%d.%d",
        &ipTemp[0], &ipTemp[1], &ipTemp[2], &ipTemp[3]);
    printf("%s\n", "1");
    if (4 != len) return false;
    uint8_t ipBinary[4] = {0};
    for (int i = 0; i < 4; ++i) ipBinary[i] = (uint8_t)ipTemp[i];
    printf("%s\n", "1");
    struct ifreq ifrequest;
    strcpy(ifrequest.ifr_name, ethernet.c_str());
    if (0 != ::ioctl(fd_, SIOCGIFHWADDR, &ifrequest)) return false;
    printf("%s\n", "1");
    return BroadcastBinary(ipBinary, (uint8_t*)ifrequest.ifr_hwaddr.sa_data, times);
}

bool BalArpBroadcast::BroadcastBinary(uint8_t ip[4], uint8_t mac[6], int times) const
{
    printf("%d\n", times);
    if (times <= 0) return false;
    if (!ip || !mac || 0 > fd_) return false;
    unsigned char bufBroadcastMac[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

    struct sockaddr_ll sendSockaddr;
    memset(&sendSockaddr, 0, sizeof(struct sockaddr_ll));
    sendSockaddr.sll_halen = htons(0x6);
    sendSockaddr.sll_ifindex = IFF_BROADCAST;
    sendSockaddr.sll_family = htons(AF_PACKET);
    sendSockaddr.sll_protocol = htons(ETH_P_ARP);
    memcpy(sendSockaddr.sll_addr, mac, 6);

    ArpPackDataDef arpData;
    memset(&arpData, 0, sizeof(ArpPackDataDef));
    memcpy(arpData.aSendIP, ip, 4);
    memcpy(arpData.aSendMac, mac, 6);
    memcpy(arpData.aDstIP, ip, 4);
    memcpy(arpData.aDstMac, bufBroadcastMac, 6);
    arpData.sOpType = htons(ARP_OP_REQUEST);
    arpData.cIpAddrLen = IP_ADDR_LEN;
    arpData.sProtocolType = htons(ETH_P_IP);
    arpData.sHardType = htons(HARD_TYPE_ETHER);
    arpData.cHardAddrLen = MAC_ADDR_LEN;

    printf("%d\n", times);

    for (int i = 0; i < times; ++i)
    {

        int ret = ::sendto(fd_, (void*)(&arpData), \
            sizeof(ArpPackDataDef), 0, (struct sockaddr*)(&sendSockaddr), sizeof(sockaddr_ll));
        if (-1 == ret) printf("%s\n", "sendto error");
    }
    return true;
}
