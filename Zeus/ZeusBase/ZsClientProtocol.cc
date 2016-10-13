#include "ZsClientProtocol.h"
using namespace std;
using namespace Zeus;

BalProtocolStatus ZsClientProtocol::CalSize(const char* buffer, uint32_t len, uint32_t* size)
{
    if (!size) return StatusFail;
    if (len < sizeof(uint32_t)) return StatusNoEnough;
    uint32_t dataSize = *((uint32_t*)buffer);
    *size = NetworkToHost32(dataSize);
    return StatusSuccess;
}

bool ZsClientProtocol::ZsClientProtocol::Encode(const char* buffer, uint32_t len, BalHandle<BalChannel> channel)
{
    if (!buffer || !channel) return false;
    uint32_t dataSize = HostToNetwork32(len);
    return (channel->WriteRawBuffer((const char*)(&dataSize), sizeof(uint32_t)))
        && (channel->WriteRawBuffer(buffer, len));
}

bool ZsClientProtocol::Decode(const char* buffer, uint32_t len, BalHandle<BalChannel> channel)
{
    if (!buffer || !channel || len < sizeof(uint32_t)) return false;
    char* bufferData = (char*)(buffer) + sizeof(uint32_t);
    return channel->OnReceiveBuffer(bufferData, len - sizeof(uint32_t));
}
