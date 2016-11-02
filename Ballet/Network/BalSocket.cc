#include "BalSocket.h"
using namespace Ballet::Network;

BalSocket::BalSocket(int fd):fd_(fd)
{
}

BalSocket::~BalSocket()
{
    if (0 != fd_)
    {
        ::close(fd_); fd_ = 0;
    }
}

bool BalSocket::IsV6Socket() const
{
    struct sockaddr addr;
    memset((void*)&addr, 0, sizeof(sockaddr));
    socklen_t len = (socklen_t)sizeof(sockaddr);
    ::getsockname(fd_, &addr, &len);
    return AF_INET6 == addr.sa_family;
}

bool BalSocket::SetReuseAddr(bool set) throw()
{
    if (0 == fd_) return false;
    int val = set? 1: 0;
    return 0 == ::setsockopt(fd_,\
    SOL_SOCKET, SO_REUSEADDR, &val, (socklen_t)(sizeof(int)));
}

bool BalSocket::SetReusePort(bool set) throw()
{
#ifdef SO_REUSEPORT
    if (0 == fd_) return false;
    int val = set? 1: 0;
    return 0 == ::setsockopt(fd_,\
    SOL_SOCKET, SO_REUSEPORT, &val, (socklen_t)(sizeof(int)));
#else
    return false;
#endif
}

uint32_t BalSocket::ReadBuffer(char* buffer, uint32_t size, bool* close) const
{
    if (0 == fd_ || nullptr_() == buffer || 0 == size)
    {
        if (close) *close = false; return 0;
    }

    int readSize = ::read(fd_, buffer, size);
    if (0 == readSize || (-1 == readSize && errno != EAGAIN))
    {
        if (close) *close = true; return 0;
    }

    if (readSize < 0)
    {
        readSize = 0;
    }

    if (close)
    {
        *close = false;
    }
    return (uint32_t)readSize;
}

uint32_t BalSocket::WriteBuffer(const char* buffer, uint32_t size, bool* close) const
{
    if (0 == fd_ || nullptr_() == buffer || 0 == size)
    {
        if (close) *close = false; return 0;
    }

    int writeSize = ::write(fd_, buffer, size);
    if (0 == writeSize || (-1 == writeSize && errno != EAGAIN))
    {
        if (close) *close = true; return 0;
    }

    if (writeSize < 0)
    {
        writeSize = 0;
    }

    if (close)
    {
        *close = false;
    }
    return (uint32_t)writeSize;
}
