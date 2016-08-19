#include "BalSocket.h"
using namespace Ballet::Network;

BalSocket::BalSocket(int fd):fd_(fd)
{
}

BalSocket::~BalSocket()
{
    if (0 != fd_)
    {
        ::close(fd_);
    }
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
