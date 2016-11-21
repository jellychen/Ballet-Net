#include "ZsStoreCenter.h"
using namespace Zeus;

ZsStoreCenter::ZsStoreCenter(const char* dir, ZsDataStoreOptions& opt)
{
    workDir_ = dir; storeOptions_ = opt;
}

ZsStoreCenter::~ZsStoreCenter()
{

}
