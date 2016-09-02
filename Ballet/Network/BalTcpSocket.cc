#include "BalTcpSocket.h"
using namespace Ballet;
using namespace Network;

BalTcpSocket::BalTcpSocket(bool v6):BalSocket(0)
{
    if (true == v6)
    {
        fd_ = ::socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
    }
    else
    {
        fd_ = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    }
}

bool BalTcpSocket::Close() throw()
{
    if (0 == fd_) return false;
    ::close(fd_); fd_ = 0;
    return true;
}

bool BalTcpSocket::Listen() throw()
{
    if (0 == fd_) return false;
    return 0 == ::listen(fd_, SOMAXCONN);
}

bool BalTcpSocket::Accpet(int* id) throw()
{
    if (0 == fd_ || nullptr_() == id) return false;
    struct sockaddr_in6 clientAddr;
    socklen_t socketLen = sizeof(clientAddr);
    *id = ::accept(fd_, (sockaddr*)&clientAddr, &socketLen);
    return *id > 0;
}

bool BalTcpSocket::SetNoBlock() throw()
{
    if (0 == fd_) return false;
    int status = ::fcntl(fd_, F_GETFL, 0);
    status |= O_NONBLOCK |FD_CLOEXEC;
    return 0 == ::fcntl(fd_, F_SETFD, status);
}

bool BalTcpSocket::ShutdownWrite() throw()
{
    if (0 == fd_) return false;
    return ::shutdown(fd_, SHUT_WR) == 0;
}

bool BalTcpSocket::SetNoDelay(bool set) throw()
{
    if (0 == fd_) return false;
    int val = set? 1: 0;
    return 0 == ::setsockopt(fd_,\
    IPPROTO_TCP, TCP_NODELAY, &val, (socklen_t)(sizeof(int)));
}

bool BalTcpSocket::SetKeepAlive(bool set) throw()
{
    if (0 == fd_) return false;
    int val = set? 1: 0;
    return 0 == ::setsockopt(fd_,\
    SOL_SOCKET, SO_KEEPALIVE, &val, (socklen_t)(sizeof(int)));
}

bool BalTcpSocket::BindAddress(BalHandle<BalInetAddress> addr) throw()
{
    if (0 == fd_ || !addr) return false;
    return 0 == ::bind(fd_,\
    addr->GetSocketAddr(), (socklen_t)(sizeof(sockaddr_in6))) >= 0;
}
