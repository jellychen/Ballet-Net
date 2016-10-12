#include "BalInetAddress.h"
using namespace Ballet::Network;

BalInetAddress::BalInetAddress(struct sockaddr* addr)
{
    SetAddr(addr);
}

BalInetAddress::BalInetAddress(struct sockaddr_in& addr):addr_(addr)
{
    v6_ = false; addr_ = addr;
}

BalInetAddress::BalInetAddress(struct sockaddr_in6& addrV6):addrV6_(addrV6)
{
    v6_ = true; addrV6_ = addrV6;
}

BalInetAddress::BalInetAddress(uint16_t port, bool lookback, bool v6)
{
    if (true == v6)
    {
        v6_ = true;
        bzero(&addrV6_, sizeof(sockaddr_in6));
        addrV6_.sin6_family = AF_INET6;
        addrV6_.sin6_addr = lookback? in6addr_loopback: in6addr_any;
        addrV6_.sin6_port = HostToNetwork16(port);
    }
    else
    {
        v6_ = false;
        bzero(&addr_, sizeof(sockaddr_in));
        addr_.sin_family = AF_INET;
        in_addr_t addr = lookback? INADDR_LOOPBACK: INADDR_ANY;
        addr_.sin_addr.s_addr = HostToNetwork32(addr);
        addr_.sin_port = HostToNetwork16(port);
    }
}

BalInetAddress::BalInetAddress(const char* ip, uint16_t port, bool v6)
{
    if (true == v6)
    {
        v6_ = true;
        bzero(&addrV6_, sizeof(sockaddr_in6));
        addrV6_.sin6_family = AF_INET6;
        addrV6_.sin6_port = HostToNetwork16(port);
        ::inet_pton(AF_INET6, ip, &addrV6_.sin6_addr);
    }
    else
    {
        v6_ = false;
        bzero(&addr_, sizeof(sockaddr_in));
        addr_.sin_family = AF_INET;
        addr_.sin_port = HostToNetwork16(port);
        ::inet_pton(AF_INET, ip, &addr_.sin_addr);
    }
}

bool BalInetAddress::IsV6() const
{
    return v6_;
}

std::string BalInetAddress::GetIp() const
{
    char buffer[64] = {0};
    if (true == v6_)
    {
        ::inet_ntop(AF_INET6, &addrV6_.sin6_addr, buffer, 64);
    }
    else
    {
        ::inet_ntop(AF_INET, &addr_.sin_addr, buffer, 64);
    }
    return std::string(buffer);
}

uint16_t BalInetAddress::GetPort() const
{
    if (true == v6_)
    {
        return NetworkToHost16(addrV6_.sin6_port);
    }
    else
    {
        return NetworkToHost16(addr_.sin_port);
    }
}

bool BalInetAddress::SetAddr(struct sockaddr* addr)
{
    if (!addr) return false;
    if (AF_INET6 == addr->sa_family)
    {
        v6_ = true; addrV6_ = *((sockaddr_in6*)addr);
    }
    else
    {
        v6_ = false; addr_ = *((sockaddr_in*)addr);
    }
    return true;
}

struct sockaddr* BalInetAddress::GetSocketAddr() const
{
    return (struct sockaddr*)(&addrV6_);
}
