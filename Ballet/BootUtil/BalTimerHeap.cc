#include "BalTimerHeap.h"
using namespace Ballet::BootUtil;

BalTimeHeap::BalTimeHeap()
{
    cacheInfo_ = 10000;
    BalTimerNode node = {nullptr_(), 0, 0};
    heapArray_.push_back(node);
}

BalTimeHeap::~BalTimeHeap()
{
    while (infoPool_.size() > 0)
    {
        delete(infoPool_.front());
        infoPool_.pop_front();
    }

    for (size_t i = 1; i < heapArray_.size(); ++i)
    {
        delete heapArray_[i].info_;
    }
}

bool BalTimeHeap::Tick(BalHandle<BalTimer>& timer)
{
    int64_t current = timestamp_.Current();
    while (true)
    {
        if (heapArray_.size() <= 1) break;
        if (heapArray_[1].timeout_ > current) break;
        if (heapArray_[1].tickTime_ == current) break;

        BalTimerNode node = heapArray_[1];
        if (false == node.info_->loop_)
        {
            this->RemoveTimerNode(1);
            long callbackHash = node.info_->callback_.HashCode();
            BalTimerIndex timerIndex = {node.info_->id_, callbackHash};
            mapTimerPoolT::iterator iter = indexPool_.find(timerIndex);
            if (indexPool_.end() != iter) indexPool_.erase(iter);

            if (node.info_->callback_ && node.info_->callback_->IsCallable())
            {
                node.info_->callback_->OnTime(node.info_->id_, timer);
            }

            ReleaseInformation(node.info_);
            node.info_ = nullptr_();
        }
        else
        {
            if (node.info_->callback_ && node.info_->callback_->IsCallable())
            {
                node.info_->callback_->OnTime(node.info_->id_, timer);
                if (heapArray_.size() > 1 && node.info_->id_ == heapArray_[1].info_->id_
                        && node.info_->callback_ == heapArray_[1].info_->callback_)
                {
                    this->RemoveTimerNode(1);
                    node.tickTime_ = current;
                    node.timeout_ = node.timeout_ + node.info_->timeSpec_;
                    this->AddTimerNode(node);
                }
            }
            else
            {
                this->RemoveTimerNode(1);
                ReleaseInformation(node.info_);
            }
        }
    }
    return true;
}

bool BalTimeHeap::SetTimerOut(int id, BalTimerCallback& callback, uint32_t time)
{
    if (!callback || !callback->IsCallable()) return false;
    return BalTimeHeap::SetTimerNode(id, callback, time, false);
}

bool BalTimeHeap::SetTimerLoop(int id, BalTimerCallback& callback, uint32_t time)
{
    if (!callback || !callback->IsCallable()) return false;
    return BalTimeHeap::SetTimerNode(id, callback, time, true);
}

bool BalTimeHeap::RemoveTimer(int id, BalTimerCallback& callback)
{
    if (!callback || !callback->IsCallable()) return false;
    long hashCode = callback.HashCode();
    if (0 == hashCode) return false;
    BalTimerIndex timerIndex = {id, hashCode};
    mapTimerPoolT::iterator iter = indexPool_.find(timerIndex);
    if (indexPool_.end() == iter) return false;

    uint32_t index = iter->second->index_; indexPool_.erase(iter);
    ReleaseInformation(heapArray_[index].info_);
    heapArray_[index].info_ = nullptr_();
    return RemoveTimerNode(index);
}

int BalTimeHeap::LastestTimeout() const
{
    if (1 >= heapArray_.size())
    {
        return INT_MAX;
    }

    int64_t time = heapArray_[1].timeout_ - timestamp_.Current();
    if (time > INT_MAX) return INT_MAX;
    return time > 0 ?time :0;
}

bool BalTimeHeap::AddTimerNode(BalTimerNode& node)
{
    uint32_t index = heapArray_.size();
    node.info_->index_ = index;
    heapArray_.push_back(node);

    while (true)
    {
        uint32_t parentIndex = index/2;
        if (0 == parentIndex) break;
        if (heapArray_[parentIndex].timeout_ <= heapArray_[index].timeout_) break;
        BalTimerNode node = heapArray_[parentIndex];
        heapArray_[parentIndex] = heapArray_[index];
        heapArray_[index] = node; node.info_->index_ = index;
    }
    return true;
}

bool BalTimeHeap::RemoveTimerNode(uint32_t index)
{
    if (index < 1 || index >= heapArray_.size()) return false;
    uint32_t lastIndex = heapArray_.size() -1;
    if (lastIndex == index)
    {
        heapArray_.resize(lastIndex);
    }
    else
    {
        heapArray_[index] = heapArray_[lastIndex];
        heapArray_[index].info_->index_ = index;
        heapArray_.resize(lastIndex); lastIndex--;

        uint32_t currentIndex = index;
        while (true)
        {
            if (currentIndex >= lastIndex) break;
            uint32_t minIndex = currentIndex; uint32_t leftIndex = currentIndex *2;
            if (leftIndex <= lastIndex && heapArray_[minIndex].timeout_ > heapArray_[leftIndex].timeout_)
            {
                minIndex = leftIndex;
            }

            uint32_t rightIndex = currentIndex *2 +1;
            if (rightIndex <= lastIndex && heapArray_[minIndex].timeout_ > heapArray_[rightIndex].timeout_)
            {
                minIndex = rightIndex;
            }
            if (minIndex == currentIndex) break;

            BalTimerNode node = heapArray_[currentIndex];
            heapArray_[currentIndex] = heapArray_[minIndex];
            heapArray_[currentIndex].info_->index_ = currentIndex;
            heapArray_[minIndex] = node; node.info_->index_ = minIndex;
            currentIndex = minIndex;
        }
    }
    return true;
}

bool BalTimeHeap::SetTimerNode(int id, BalTimerCallback& callback, uint32_t time, bool loop)
{
    if (!callback || !callback->IsCallable()) return false;
    long hashCode = callback.HashCode();
    if (0 == hashCode) return false;
    BalTimerIndex timerIndex = {id, hashCode};
    mapTimerPoolT::iterator iter = indexPool_.find(timerIndex);
    if (indexPool_.end() != iter) return false;

    BalTimerInformation* info = nullptr_();
    if (infoPool_.size() <= 0)
    {
        info = new(std::nothrow)BalTimerInformation();
    }
    else
    {
        info = infoPool_.front(); infoPool_.pop_front();
    }
    if (nullptr_() == info) return false;

    info->timeSpec_ = time; info->callback_ = callback;
    info->id_ = id; info->index_ = -1; info->loop_ = loop;
    indexPool_[timerIndex] = info;
    BalTimerNode node = {info, timestamp_.Current() +time, 0};
    return AddTimerNode(node);
}

bool BalTimeHeap::ReleaseInformation(BalTimerInformation* info)
{
    if (!info) return false;
    if (cacheInfo_ <= infoPool_.size())
    {
        delete(info);
    }
    else
    {
        infoPool_.push_back(info);
    }
}
