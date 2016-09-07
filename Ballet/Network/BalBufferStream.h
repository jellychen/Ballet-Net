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
            bool AppendBuffer(const char*, size_t);
            void ConsumeBuffer(size_t);
            char* RawBuffer() const;

        private:
            char* buffer_;
            size_t start_, end_, capacity_;
        };
    }
}
#endif
