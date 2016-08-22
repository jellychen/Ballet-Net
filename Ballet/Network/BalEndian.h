#ifndef Ballet_Common_BalEndian_H
#define Ballet_Common_BalEndian_H
#include "Common/BalInct.h"
#include "BalNetworkInct.h"

namespace Ballet
{
    namespace Network
    {
        inline uint64_t HostToNetwork64(uint64_t host64)
        {
          return htobe64(host64);
        }

        inline uint32_t HostToNetwork32(uint32_t host32)
        {
          return htobe32(host32);
        }

        inline uint16_t HostToNetwork16(uint16_t host16)
        {
          return htobe16(host16);
        }

        inline uint64_t NetworkToHost64(uint64_t net64)
        {
          return be64toh(net64);
        }

        inline uint32_t NetworkToHost32(uint32_t net32)
        {
          return be32toh(net32);
        }

        inline uint16_t NetworkToHost16(uint16_t net16)
        {
          return be16toh(net16);
        }
    }
}
#endif
