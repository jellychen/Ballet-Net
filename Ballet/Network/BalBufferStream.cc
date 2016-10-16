#include "BalBufferStream.h"
using namespace Ballet;
using namespace Network;

BalBufferStream::BalBufferStream():start_(0),end_(0),capacity_(32)
{
    buffer_ = (char*)malloc(capacity_);
    if (nullptr_() == buffer_)
    {
        throw std::runtime_error("BalBufferArray Construct Failed");
    }
}

BalBufferStream::~BalBufferStream()
{
    if (nullptr_() != buffer_)
    {
        free(buffer_);
    }
}

bool BalBufferStream::Clear()
{
    if (nullptr_() != buffer_)
    {
        free(buffer_);
    }
    start_ = 0; end_ = 0; capacity_ = 32;
    buffer_ = (char*)malloc(capacity_);
    return buffer_;
}

size_t BalBufferStream::GetSize()
{
    return end_ - start_;
}

size_t BalBufferStream::Capacity() const
{
    return capacity_;
}

bool BalBufferStream::AppendBuffer(const char* buffer, size_t len)
{
    if (nullptr_() == buffer || 0 >= len) return false;
    if (capacity_ - end_ >= len)
    {
        memcpy(buffer_ + end_, buffer, len);
        end_ += len;
    }
    else if (start_ + capacity_ - end_ >= len)
    {
        size_t dataLen = end_ - start_;
        if (0 != start_)
        {
            memcpy(buffer_, buffer_ + start_, dataLen);
        }
        start_ = 0; end_ = dataLen;
        memcpy(buffer_ + dataLen, buffer, len);
        end_ += len;
    }
    else
    {
        size_t dataLen = end_ - start_;
        size_t needSize = dataLen + len;
        size_t mallocSize = capacity_;
        while (mallocSize <= needSize)
        {
            mallocSize *= 1.5;
        }

        char* newBuffer = (char*)malloc(mallocSize);
        if (nullptr_() == newBuffer) return false;
        memcpy(newBuffer, buffer_+start_, dataLen);
        memcpy(newBuffer + dataLen, buffer, len); free(buffer_);
        buffer_ = newBuffer; start_ = 0; end_ = needSize; capacity_ = mallocSize;
    }
    return true;
}

void BalBufferStream::ConsumeBuffer(size_t len)
{
    if (0 >= len) return;
    start_ += len;
    if (start_ > end_) start_ = end_;
}

char* BalBufferStream::RawBuffer() const
{
    return buffer_ + start_;
}
