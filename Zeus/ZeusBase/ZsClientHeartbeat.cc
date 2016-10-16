#include "ZsClientHeartbeat.h"
using namespace Zeus;

ZsClientHeartbeat::ZsClientHeartbeat()
{
    ZsClientData bufferData_;
    bufferData_.type_ = ZsClientDataHeartbeat;
    bufferData_.Serialize(heartbeatBuffer_, true);
}
