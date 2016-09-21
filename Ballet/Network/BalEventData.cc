#include "BalEventData.h"
using namespace Ballet;
using namespace Network;

BalEventDataManager::BalEventDataManager(uint32_t size)
{
    for (uint32_t i = 0; i < size; ++i)
    {
        BalEventData* data = new(std::nothrow)BalEventData();
        if (data)
        {
            listPool_.push_back(data);
        }
    }
}

BalEventDataManager::~BalEventDataManager()
{
    listPoolT::iterator iter = listPool_.begin();
    while (iter != listPool_.end())
    {
        BalEventData* data = *iter++;
        delete data;
    }
    listPool_.clear();
}

BalEventData* BalEventDataManager::GetOne()
{
    BalEventData* data = nullptr_();
    if (listPool_.size() > 0)
    {
        data = listPool_.front();
        listPool_.pop_front();
    }
    else
    {
        data = new(std::nothrow)BalEventData();
    }

    if (data) data->index_ = -1;
    return data;
}

void BalEventDataManager::RevertBack(BalEventData* data)
{
    if (!data) return;
    if ((uint32_t)listPool_.size() >= maxSize_)
    {
        delete data;
    }
    else
    {
        listPool_.push_back(data);
    }
}
