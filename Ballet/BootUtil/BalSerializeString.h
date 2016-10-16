#ifndef Ballet_BootUtil_BalSerializeString_H
#define Ballet_BootUtil_BalSerializeString_H
#include "Common/BalInct.h"
#include "BalEndian.h"

namespace Ballet
{
    namespace BootUtil
    {
        struct BalStringObject_T: public std::string
        {
            typedef BalStringObject_T tClass;
            inline int Size() { return (int)size() + sizeof(uint32_t);}
            inline int Serialize(std::string& str, bool endian)
            {
                uint32_t dataSize = (uint32_t)size();
                if (endian) { dataSize = htoni(dataSize);}
                str.append((char*)&dataSize, sizeof(uint32_t));
                str.append(c_str(), size());
                return size() + sizeof(uint32_t);
            }

            inline int Serialize(char* buffer, uint32_t capacity, bool endian)
            {
                uint32_t dataSize = (uint32_t)size();
                if (!buffer || capacity < (dataSize + sizeof(uint32_t))) return -1;
                if (endian) { dataSize = htoni(dataSize);}
                memcpy((char*)buffer, (void*)&dataSize, sizeof(uint32_t));
                memcpy((char*)buffer + sizeof(uint32_t), (void*)c_str(), size());
                return (int)size() + sizeof(uint32_t);
            }

            inline int UnSerialize(char* buffer, uint32_t capacity, bool endian)
            {
                if (!buffer || capacity < sizeof(uint32_t)) return -1;
                uint32_t dataSize = *((uint32_t*)(buffer));
                if (endian) { dataSize = ntohi(dataSize);}
                if (capacity < dataSize + sizeof(uint32_t)) return -1;
                
                append(buffer + sizeof(uint32_t), dataSize);
                return dataSize + sizeof(uint32_t);
            }
        };

        typedef BalStringObject_T BalPackString;
    }
}
#endif
