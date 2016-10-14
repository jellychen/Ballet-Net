#ifndef Ballet_BootUtil_BalSerializeComponent_H
#define Ballet_BootUtil_BalSerializeComponent_H
#include "Common/BalInct.h"
#include "BalEndian.h"

namespace Ballet
{
    namespace BootUtil
    {
        class BalSerializeComponent
        {
        public:
            virtual int Size() = 0;
            virtual int Serialize(std::string& str, bool endian) = 0;
            virtual int Serialize(char* buffer, uint32_t capacity, bool endian) = 0;
            virtual int UnSerialize(char* buffer, uint32_t capacity, bool endian) = 0;
        };
    }
}
#endif
