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
/*
    struct ifreq ifrequest;
    strcpy(ifrequest.ifr_name, "eth0");
    ::ioctl(fd_, SIOCGIFHWADDR, &ifrequest);
    printf( "%02x:%02x:%02x:%02x:%02x:%02x\n ",
            (unsigned   char)ifrequest.ifr_hwaddr.sa_data[0],
            (unsigned   char)ifrequest.ifr_hwaddr.sa_data[1],
            (unsigned   char)ifrequest.ifr_hwaddr.sa_data[2],
            (unsigned   char)ifrequest.ifr_hwaddr.sa_data[3],
            (unsigned   char)ifrequest.ifr_hwaddr.sa_data[4],
            (unsigned   char)ifrequest.ifr_hwaddr.sa_data[5]);
*/
}

BalArpBroadcast::~BalArpBroadcast()
{
    if (0 != fd_)
    {
        ::close(fd_);
    }
}

bool BalArpBroadcast::Broadcast(std::string ip, std::string mac) const
{
    int macTemp[6] = {0};
    int len = sscanf(mac.c_str(), "%02x:%02x:%02x:%02x:%02x:%02x",
        &macTemp[0], &macTemp[0], &macTemp[0], &macTemp[0], &macTemp[0], &macTemp[0]);
    if (6 != len) return false;
    int ipTemp[6] = {0};
    len = sscanf(ip.c_str(), "%d.%d.%d.%d",
        &ipTemp[0], &ipTemp[0], &ipTemp[0], &ipTemp[0]);
    if (4 != len) return false;

    uint8_t ipBinary[4] = {0};
    for (int i = 0; i < 4; ++i)
    {
        ipBinary[i] = (uint8_t)ipTemp[i];
    }

    uint8_t macBinary[6] = {0};
    for (int i = 0; i < 6; ++i)
    {
        macBinary[i] = (uint8_t)macTemp[i];
    }

    return BroadcastBinary(ipBinary, macBinary);
}

bool BalArpBroadcast::BroadcastHardware(std::string ip, std::string ethernet) const
{
    struct ifreq ifrequest;
    strcpy(ifrequest.ifr_name, ethernet.c_str());
    ::ioctl(fd_, SIOCGIFHWADDR, &ifrequest);
    
    return true;
}

bool BalArpBroadcast::BroadcastBinary(uint8_t ip[4], uint8_t mac[6]) const
{
    return true;
}
