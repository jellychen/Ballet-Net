#include "ZsNodeMember.h"
using namespace Zeus;
#define ZSNODE_MEMBER_RECONNECT_TIMER 0

ZsNodeMember::ZsNodeMember(BalHandle<ZsNodeContext> context, BalHandle<BalInetAddress> addr)
    :clientCallback_(this), timerCallback_(this), connetTime_(0)
{
    if (!context || !context->eventLoop_ || !addr)
    {
        throw std::runtime_error("ZsNodeMember Construct Failed!");
    }

    connectAddr_ = addr; context_ = context;
    timerCallback_->HookOnTime(&ZsNodeMember::OnTime);
    clientCallback_->HookOnConnect(&ZsNodeMember::OnConnect);
    clientCallback_->HookOnClose(&ZsNodeMember::OnClose);
    clientCallback_->HookOnReceive(&ZsNodeMember::OnReceive);

    BalHandle<IBalProtocol> protocol(new ZsNodeNetProtocol());
    BalHandle<ZsWorkboardOptions> options = context->options_;
    BalHandle<BalTcpClient> client(new BalTcpClient(
        context->eventLoop_, protocol, options->maxPackageSize_,
        clientCallback_, options->maxTimeout_, options->maxReadBufferSize_,
        options->maxWriteBufferSize_));
    tcpClient_ = client;

    ZsNodeMember::Connect();
}

ZsNodeMember::~ZsNodeMember()
{

}

bool ZsNodeMember::SendBuffer(const char* buffer, uint32_t len)
{
    if (!tcpClient_)
    {
        return false;
    }
    return tcpClient_->WriteBuffer(buffer, len);
}

bool ZsNodeMember::Connect()
{
    if (!connectAddr_ || !context_ || !context_->options_)
    {
        return false;
    }

    if (tcpClient_->IsConnected())
    {
        return false;
    }

    connetTime_ = BalTimeStamp::GetCurrent();
    tcpClient_->Connect(connectAddr_, context_->options_->maxConnectTimeout_);
    tcpClient_->SetNoDelay(true); tcpClient_->SetReuseAddr(true);
    return true;
}

bool ZsNodeMember::CaseTimeoutReconnect()
{
    if (!context_ || !context_->options_ || !context_->eventLoop_)
    {
        return false;
    }

    uint32_t reconnectTimeout = context_->options_->maxReConnectTimeout_;
    uint32_t connectInterval = (uint32_t)(BalTimeStamp::GetCurrent() - connetTime_);
    if (connectInterval >=  reconnectTimeout)
    {
        ZsNodeMember::Connect();
    }
    else
    {
        context_->eventLoop_->SetTimerOut(ZSNODE_MEMBER_RECONNECT_TIMER,
            timerCallback_, reconnectTimeout - connectInterval);
    }
    return true;
}

void ZsNodeMember::OnTime(uint32_t id, BalHandle<BalTimer>)
{
    if (ZSNODE_MEMBER_RECONNECT_TIMER == id)
    {
        ZsNodeMember::Connect();
    }
}

void ZsNodeMember::OnConnect(BalHandle<BalTcpClient> client, bool success)
{
    if (false == success && connectAddr_)
    {
        ZsNodeMember::CaseTimeoutReconnect();
    }
}

void ZsNodeMember::OnClose(BalHandle<BalTcpClient> client, bool accord)
{
    ZsNodeMember::CaseTimeoutReconnect();
}

void ZsNodeMember::OnReceive(BalHandle<BalTcpClient> client, const char* buffer, uint32_t len)
{

}
