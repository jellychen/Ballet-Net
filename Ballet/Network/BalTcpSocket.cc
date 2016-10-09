#include "BalTcpSocket.h"
using namespace Ballet;
using namespace Network;

BalTcpSocket::BalTcpSocket(int fd):BalSocket(fd)
{

}

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
    int clientFd = ::accept(fd_, (sockaddr*)&clientAddr, &socketLen);
    if (clientFd == -1 && errno != EAGAIN
        && errno != ECONNABORTED && errno != EPROTO && errno != EINTR)
    {
        // error
    }
    *id = clientFd;
    return !(-1 == clientFd && EAGAIN == errno);
}

bool BalTcpSocket::SetNoBlock() throw()
{
    if (0 == fd_) return false;
    return 0 == ::fcntl(fd_, F_SETFL, fcntl(fd_, F_GETFL)|O_NONBLOCK|FD_CLOEXEC);
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
    return 0 == ::setsockopt(fd_, IPPROTO_TCP, TCP_NODELAY, &val, sizeof(int));
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
    addr->GetSocketAddr(), (socklen_t)(sizeof(sockaddr_in6)));
}

bool BalTcpSocket::Connect(BalHandle<BalInetAddress> addr, bool* connecting) throw()
{
    if (0 == fd_ || !addr) return false;
    int ret = ::connect(fd_,\
    addr->GetSocketAddr(), (socklen_t)(sizeof(sockaddr_in6)));
    if (0 == ret) return true;
    if (0 > ret && EINPROGRESS == errno && connecting)
    {
        *connecting = true;
    }
    return false;
}
