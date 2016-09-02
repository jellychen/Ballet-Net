#ifndef Ballet_Common_BalBufferStream_H
#define Ballet_Common_BalBufferStream_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace Network
    {
        class BalBufferStream :public BalNoCoable
        {
        public:
            BalBufferStream();
            virtual ~BalBufferStream();

        public:
            size_t GetSize();
            size_t Capacity() const;
            bool Clear();
            bool AppendBuffer(const uint8_t*, size_t);
            void ConsumeBuffer(size_t);
            uint8_t* RawBuffer() const;

        private:
            uint8_t* buffer_;
            size_t start_, end_, capacity_;
        };
    }
}
#endif
