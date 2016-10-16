#ifndef Ballet_BootUtil_BalSerializeArray_H
#define Ballet_BootUtil_BalSerializeArray_H
#include "Common/BalInct.h"
#include "BalEndian.h"

namespace Ballet
{
    namespace BootUtil
    {
        template<typename T> struct BalPackArray: public std::vector<T>
        {
            typedef BalPackArray tClass;
            inline int Size()
            {
                int dataSize = 0;
                for (size_t i = 0; i < size(); ++i)
                {
                    dataSize += at(i).Size();
                }
                return dataSize + sizeof(uint32_t);
            }

            inline int Serialize(std::string& str, bool endian)
            {
                uint32_t dataSize = (uint32_t)size();
                if (endian) { dataSize = htoni(dataSize);}
                str.append((char*)&dataSize, sizeof(uint32_t));

                int rawSize = 0;
                for (size_t i = 0; i < size(); ++i)
                {
                    rawSize += at(i).Serialize(str, endian);
                }
                return rawSize + sizeof(uint32_t);
            }

            inline int Serialize(char* buffer, uint32_t capacity, bool endian)
            {
                if (!buffer || capacity < sizeof(uint32_t)) return -1;
                uint32_t dataSize = (uint32_t)size();
                if (endian) { dataSize = htoni(dataSize);}
                memcpy((char*)buffer, (void*)&dataSize, sizeof(uint32_t));
                capacity -= sizeof(uint32_t);

                int rawSize = sizeof(uint32_t);
                char* curBuffer = buffer +sizeof(uint32_t);
                for (size_t i = 0; i < size(); ++i)
                {
                    int innerSize = at(i).Serialize(curBuffer, capacity, endian);
                    if (-1 == innerSize) return -1;
                    curBuffer += innerSize; rawSize += innerSize; capacity -= innerSize;
                }
                return rawSize;
            }

            inline int UnSerialize(char* buffer, uint32_t capacity, bool endian)
            {
                if (!buffer || capacity < sizeof(uint32_t)) return -1;
                uint32_t dataSize = *((uint32_t*)buffer);
                if (endian) { dataSize = ntohi(dataSize);}
                capacity -= sizeof(uint32_t);

                int rawSize = sizeof(uint32_t); resize(dataSize);
                char* curBuffer = buffer + sizeof(uint32_t);
                for (uint32_t i = 0; i < dataSize; ++i)
                {
                    int innerSize = at(i).UnSerialize(curBuffer, capacity, endian);
                    if (-1 == innerSize) return -1;
                    curBuffer += innerSize; rawSize += innerSize; capacity -= innerSize;
                }
                return rawSize;
            }
        };
    }
}
#endif
