#include "ZsCollocationClient.h"
using namespace Zeus;

ZsCollocationClient::ZsCollocationClient(BalHandle<BalEventLoop> loop,
    uint32_t connectTimeout, uint32_t heartbeat, uint32_t timeout,
    uint32_t maxPackage, uint32_t maxReadBufferSize, uint32_t maxWriteBufferSize)
    :timerCallback_(this), tcpCallback_(this)
    ,heartbeatTime_(heartbeat) ,tcpProtocol_(new ZsClientProtocol())
{
    eventLoop_ = loop;
    timeoutTime_ = timeout;
    heartbeatTime_ = heartbeat;
    maxPackageSize_ = maxPackage;
    connectTimeout_ = connectTimeout;
    maxReadBufferSize_ = maxReadBufferSize;
    maxWriteBufferSize_ = maxWriteBufferSize;

    timerCallback_->HookOnTime(&ZsCollocationClient::OnTime);
    tcpCallback_->HookOnConnect(&ZsCollocationClient::OnConnect);
    tcpCallback_->HookOnReceive(&ZsCollocationClient::OnReceive);
    tcpCallback_->HookOnClose(&ZsCollocationClient::OnClose);

    if (time <= 0 || !eventLoop_)
    {
        throw std::runtime_error("ZsCollocationClient Construct Failed");
    }
}

bool ZsCollocationClient::Start(BalHandle<ZsNodeTree> nodeTree, BalHandle<BalInetAddress> addr)
{
    if (!nodeTree || !addr) return false;
    printf("%s\n", "ZsCollocationClient Start");
    nodeTree_ = nodeTree; tcpAddress_ = addr;

    BalHandle<BalTcpClient> client(
        new BalTcpClient(false, eventLoop_, tcpProtocol_,
            maxPackageSize_, tcpCallback_, timeoutTime_,
            maxReadBufferSize_, maxWriteBufferSize_)
    );

    tcpClient_ = client;
    if (tcpClient_)
    {
        tcpClient_->SetNoDelay(true);
        tcpClient_->SetReuseAddr(true);
        tcpClient_->Connect(addr, connectTimeout_);
    }
    return true;
}

void ZsCollocationClient::OnTime(uint32_t id, BalHandle<BalTimer> timer)
{
    if (tcpClient_)
    {
        const std::string& hbBuffer = heartbeat_.heartbeatBuffer_;
        tcpClient_->WriteBuffer(hbBuffer.c_str(), hbBuffer.size());
    }
}

void ZsCollocationClient::OnConnect(BalHandle<BalTcpClient> client, bool success)
{
    if (success)
    {
        printf("%s\n", "OnConnect true");
        eventLoop_->SetTimerLoop(0, timerCallback_, heartbeatTime_);
    }
    else
    {
        printf("%s\n", "OnConnect false");
    }
}

void ZsCollocationClient::OnReceive(BalHandle<BalTcpClient> client, const char* buffer, uint32_t len)
{
    long stime = BalCurrentTime();

    ZsClientData receData;
    if (-1 != receData.UnSerialize((char*)buffer, len, false) && nodeTree_)
    {
        BalPackArray<ZsClientDataAddr>& arrayData  = receData.array_;
        if (ZsClientDataAdd == receData.type_.rawData_)
        {
            for (size_t i = 0; i < arrayData.size(); ++i)
            {
                ZsClientDataAddr& service = arrayData.at(i);
                BalPackArray<BalPackString>& addr = service.address_;
                for (size_t j = 0; j < addr.size(); ++j)
                {
                    nodeTree_->AddServiceAddr(service.name_, addr.at(j));
                }
            }
        }
        else if (ZsClientDataRemove == receData.type_.rawData_)
        {
            for (size_t i = 0; i < arrayData.size(); ++i)
            {
                ZsClientDataAddr& service = arrayData.at(i);
                BalPackArray<BalPackString>& addr = service.address_;
                for (size_t j = 0; j < addr.size(); ++j)
                {
                    nodeTree_->DeleteServiceAddr(service.name_, addr.at(j));
                }
            }
        }
        else if (ZsClientDataCreate == receData.type_.rawData_)
        {
            nodeTree_->Clear();
            for (size_t i = 0; i < arrayData.size(); ++i)
            {
                ZsClientDataAddr& service = arrayData.at(i);
                BalPackArray<BalPackString>& addr = service.address_;
                for (size_t j = 0; j < addr.size(); ++j)
                {
                    nodeTree_->AddServiceAddr(service.name_, addr.at(j));
                }
            }
        }
    }

    printf("----- %d\n", BalCurrentTime() - stime);
}

void ZsCollocationClient::OnClose(BalHandle<BalTcpClient> client, bool accord)
{
    printf("%s\n", "OnClose true");
}
