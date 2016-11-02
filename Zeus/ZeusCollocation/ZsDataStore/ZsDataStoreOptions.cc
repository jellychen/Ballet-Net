#include "ZsDataStoreOptions.h"
using namespace Zeus;

ZsDataStoreOptions::ZsDataStoreOptions()
{
    compress_ = false;
    blockSize_ = 4 *1024;
    writeBufferSize_ = 20 *1024 *1024;
}
