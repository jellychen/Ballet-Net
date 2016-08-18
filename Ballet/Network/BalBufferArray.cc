#include "BalBufferArray.h"
using namespace Ballet;
using namespace Network;

BalBufferArray::BalBufferArray():start_(0),end_(0),capacity_(32)
{
    buffer_ = (uint8_t*)malloc(capacity_);
    if (nullptr_() == buffer_)
    {
        throw std::runtime_error("BalBufferArray Construct Failed");
    }
}

BalBufferArray::~BalBufferArray()
{
    if (nullptr_() != buffer_)
    {
        free(buffer_);
    }
}

bool BalBufferArray::Clear()
{
    if (nullptr_() != buffer_)
    {
        free(buffer_);
    }
    start_ = 0; end_ = 0; capacity_ = 32;
    buffer_ = (uint8_t*)malloc(capacity_);
    return buffer_;
}

size_t BalBufferArray::GetSize()
{
    return end_ - start_;
}

size_t BalBufferArray::Capacity() const
{
    return capacity_;
}

bool BalBufferArray::AppendBuffer(const uint8_t* buffer, size_t len)
{
    if (nullptr_() == buffer || 0 == len) return false;
    if (capacity_ - end_ > len)
    {
        memcpy(buffer_ + end_, buffer, len);
        end_ += len;
    }
    else if (start_ + capacity_ - end_ > len)
    {
        size_t dataLen = end_ - start_;
        memcpy(buffer_, buffer_ + start_, dataLen);
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

        uint8_t* newBuffer = (uint8_t*)malloc(mallocSize);
        if (nullptr_() == newBuffer) return false;
        memcpy(newBuffer, buffer_+start_, dataLen);
        memcpy(newBuffer, buffer, len); free(buffer_);
        buffer_ = newBuffer; start_ = 0; end_ = needSize; capacity_ = mallocSize;
    }
    return true;
}

void BalBufferArray::ConsumeBuffer(size_t len)
{
    start_ += len;
    if (start_ > end_) start_ = end_;
}

uint8_t* BalBufferArray::RawBuffer() const
{
    return buffer_;
}