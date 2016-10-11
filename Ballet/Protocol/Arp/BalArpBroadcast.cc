#include "BalArpDef.h"
#include "BalArpBroadcast.h"
using namespace Ballet;
using namespace Protocol;

BalArpBroadcast::BalArpBroadcast()
{
    fd_ = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
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

bool BalArpBroadcast::Broadcast(std::string ip, std::string mac, int time) const
{
    if (time <= 0) return false;
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
    return BroadcastBinary(ipBinary, macBinary, time);
}

bool BalArpBroadcast::BroadcastHardware(std::string ip, std::string ethernet, int time) const
{
    if (time <= 0) return false;
    int ipTemp[4] = {0};
    int len = sscanf(ip.c_str(), "%d.%d.%d.%d",
        &ipTemp[0], &ipTemp[1], &ipTemp[2], &ipTemp[3]);
    if (4 != len) return false;
    uint8_t ipBinary[4] = {0};
    for (int i = 0; i < 4; ++i) ipBinary[i] = (uint8_t)ipTemp[i];

    struct ifreq ifrequest;
    strcpy(ifrequest.ifr_name, ethernet.c_str());
    if (0 != ::ioctl(fd_, SIOCGIFHWADDR, &ifrequest)) return false;
    uint8_t macBinary[6] = {0};
    memcpy(macBinary, ifrequest.ifr_hwaddr.sa_data, 6 *sizeof(uint8_t));
    return BroadcastBinary(ipBinary, macBinary, time);
}

bool BalArpBroadcast::BroadcastBinary(uint8_t ip[4], uint8_t mac[6], int time) const
{
    if (time <= 0) return false;
    if (!ip || !mac || 0 > fd_) return false;
    arp_packet packet; memset(&packet, 0, sizeof(arp_packet));
    const uint8_t destIp[4] = {0xff, 0xff, 0xff, 0xff};
    const uint8_t destMac[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    memcpy(packet.eth.dest_mac, destMac, 6 *sizeof(uint8_t));
    memcpy(packet.eth.source_mac, mac, 6 *sizeof(uint8_t));
    packet.eth.ethernet_type = htons(0x0806);
    packet.arp.hardware_type = htons(0x1);
    packet.arp.protocol_type = htons(0x0800);
    packet.arp.addr_len = 6; packet.arp.protocol_len = 4;
    packet.arp.option_code = htons(0x2);
    memcpy(packet.arp.source_mac, mac, 6 *sizeof(uint8_t));
    memcpy(packet.arp.source_ip, ip, 4 *sizeof(uint8_t));
    memset(packet.arp.dest_mac, 0, 6 *sizeof(uint8_t));
    memset(packet.arp.dest_ip, 0, 4 *sizeof(uint8_t));

    struct sockaddr_ll sl; memset(&sl, 0, sizeof(sl));
    sl.sll_family = AF_PACKET; sl.sll_ifindex = IFF_BROADCAST;
    for (int i = 0; i < time; ++i)
    {
        ::sendto(fd_, &packet, sizeof(packet), 0, (struct sockaddr*)&sl, sizeof(sl));
    }
    return true;
}
