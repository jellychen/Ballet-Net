#include "BalUdpSocket.h"
using namespace Ballet;
using namespace Network;

BalUdpSocket::BalUdpSocket(int fd):BalSocket(fd)
{

}

BalUdpSocket::BalUdpSocket(bool v6):BalSocket(0)
{
    if (true == v6)
    {
        fd_ = ::socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
    }
    else
    {
        fd_ = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    }
}

bool BalUdpSocket::Close() throw()
{
    if (0 == fd_) return false;
    ::close(fd_); fd_ = 0;
    return true;
}

bool BalUdpSocket::SetNoBlock() throw()
{
    if (0 == fd_) return false;
    return 0 == ::fcntl(fd_,\
         F_SETFL, fcntl(fd_, F_GETFL)|O_NONBLOCK|FD_CLOEXEC);
}

bool BalUdpSocket::BindAddress(BalHandle<BalInetAddress> addr) throw()
{
    if (0 == fd_ || !addr) return false;
    return 0 == ::bind(fd_,\
        addr->GetSocketAddr(), (socklen_t)(sizeof(sockaddr_in6)));
}

int BalUdpSocket::ReadBufferFrom(char* buffer,
        uint32_t size, BalHandle<BalInetAddress>& addr) throw()
{
    if (0 == fd_ || !addr || !size) return 0;
    sockaddr_in6 addrTemp; socklen_t len = sizeof(sockaddr_in6);
    int ret = (int)::recvfrom(fd_, buffer, size, 0, (sockaddr*)&addrTemp, &len);
    addr->SetAddr((sockaddr*)&addrTemp);
    return ret;
}

int BalUdpSocket::SendBufferTo(const char* buffer,
        uint32_t size, BalHandle<BalInetAddress> addr) throw()
{
    if (0 == fd_ || !addr || !size) return 0;
    return (int)::sendto(fd_, buffer, size, 0,\
         addr->GetSocketAddr(), (socklen_t)(sizeof(sockaddr_in6)));
}
