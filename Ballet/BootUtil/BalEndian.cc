#include "BalEndian.h"
using namespace Ballet::BootUtil;

union HostLittelEndian_t
{
    int i; char bit;
};

inline bool IsHostMachineLittleEndian()
{
    static HostLittelEndian_t data;
    return 1 != data.bit;
}

inline int8_t htoni(int8_t iData)
{
    return iData;
}

inline int16_t htoni(int16_t iData)
{
    if (IsHostMachineLittleEndian()) return iData;
    return ((iData &0x00FF) << 8)|((iData &0xFF00) >> 8);
}

inline int32_t htoni(int32_t iData)
{
    if (IsHostMachineLittleEndian()) return iData;
    return
        ((iData &0x000000FF) << 24)|((iData &0xFF000000) >> 24)|
        ((iData &0x0000FF00) << 8 )|((iData &0x00FF0000) >> 8 );
}

inline int64_t htoni(int64_t iData)
{
    if (IsHostMachineLittleEndian()) return iData;
    return
        ((iData &0x00000000000000FF) << 56)|((iData &0xFF00000000000000) >> 56)|
        ((iData &0x000000000000FF00) << 40)|((iData &0x00FF000000000000) >> 40)|
        ((iData &0x0000000000FF0000) << 24)|((iData &0x0000FF0000000000) >> 24)|
        ((iData &0x00000000FF000000) << 8 )|((iData &0x000000FF00000000) >> 8 );
}

inline int8_t ntohi(int8_t iData)
{
    return iData;
}

inline int16_t ntohi(int16_t iData)
{
    if (IsHostMachineLittleEndian()) return iData;
    return ((iData &0x00FF) << 8)|((iData &0xFF00) >> 8);
}

inline int32_t ntohi(int32_t iData)
{
    if (IsHostMachineLittleEndian()) return iData;
    return
        ((iData &0x000000FF) << 24)|((iData &0xFF000000) >> 24)|
        ((iData &0x0000FF00) << 8 )|((iData &0x00FF0000) >> 8 );
}

inline int64_t ntohi(int64_t iData)
{
    if (IsHostMachineLittleEndian()) return iData;
    return
        ((iData &0x00000000000000FF) << 56)|((iData &0xFF00000000000000) >> 56)|
        ((iData &0x000000000000FF00) << 40)|((iData &0x00FF000000000000) >> 40)|
        ((iData &0x0000000000FF0000) << 24)|((iData &0x0000FF0000000000) >> 24)|
        ((iData &0x00000000FF000000) << 8 )|((iData &0x000000FF00000000) >> 8 );
}

inline uint8_t htoni(uint8_t iData)
{
    return iData;
}

inline uint16_t htoni(uint16_t iData)
{
    return ::htons(iData);
}

inline uint32_t htoni(uint32_t iData)
{
    return ::htonl(iData);
}

inline uint64_t htoni(uint64_t iData)
{
    if (IsHostMachineLittleEndian()) return iData;
    return
        ((iData &0x00000000000000FF) << 56)|((iData &0xFF00000000000000) >> 56)|
        ((iData &0x000000000000FF00) << 40)|((iData &0x00FF000000000000) >> 40)|
        ((iData &0x0000000000FF0000) << 24)|((iData &0x0000FF0000000000) >> 24)|
        ((iData &0x00000000FF000000) << 8 )|((iData &0x000000FF00000000) >> 8 );
}

inline uint8_t ntohi(uint8_t iData)
{
    return iData;
}

inline uint16_t ntohi(uint16_t iData)
{
    return ::ntohs(iData);
}

inline uint32_t ntohi(uint32_t iData)
{
    return ::ntohl(iData);
}

inline uint64_t ntohi(uint64_t iData)
{
    if (IsHostMachineLittleEndian()) return iData;
    return
        ((iData &0x00000000000000FF) << 56)|((iData &0xFF00000000000000) >> 56)|
        ((iData &0x000000000000FF00) << 40)|((iData &0x00FF000000000000) >> 40)|
        ((iData &0x0000000000FF0000) << 24)|((iData &0x0000FF0000000000) >> 24)|
        ((iData &0x00000000FF000000) << 8 )|((iData &0x000000FF00000000) >> 8 );
}
