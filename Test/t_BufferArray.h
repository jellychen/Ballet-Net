#include <Ballet/Common/BalInct.h>
#include <Ballet/Network/BalBufferStream.h>
using namespace Ballet;
using namespace Network;

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

void t_BufferArray_main()
{
    std::cout << "t_BufferArray_main" << std::endl;
    BalHandle<BalBufferStream> buffer(new BalBufferStream);
    for (int i = 0; i < 10000000; ++i)
    {
        unsigned char rawBuffer[1024] = {0};
        buffer->AppendBuffer(rawBuffer, 1024);
    }
}
