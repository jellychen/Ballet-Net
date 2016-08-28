#ifndef Ballet_Common_BalEventCallback_H
#define Ballet_Common_BalEventCallback_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace Network
    {
        class BalEventLoop;

        enum BalEventCallbackEnum
        {
            EventRetNone        = 0,
            EventRetAgain       = 1,
            EventRetClose       = 2,
            EventRetComplete    = 3,
            EventRetContinue    = 4,
        };

        struct IBalEventCallback :public BalCallback
        {
            // note: call when fd can read
            virtual BalEventCallbackEnum ShouldRead(int id, BalHandle<BalEventLoop> el) =0;

            // note: call when fd can write
            virtual BalEventCallbackEnum ShouldWrite(int id, BalHandle<BalEventLoop> el) =0;
        };

        BalCallbackSinkBegin(CBalEventCallback)
        BalCallbackSink(BalEventCallbackEnum, ShouldRead,  (int id, BalHandle<BalEventLoop> el), (id, el))
        BalCallbackSink(BalEventCallbackEnum, ShouldWrite, (int id, BalHandle<BalEventLoop> el), (id, el))
        BalCallbackSinkComplete()
        BalCallbackSinkPtrDefine(CBalEventCallback, IBalEventCallback)

        typedef BalHandle<IBalEventCallback> BalEventCallback;

        struct BalEventCallbackWrapper
        {
            BalEventCallback callback_;
            int index_; unsigned int status_;
        };
        typedef std::list<BalHandle<BalElement> > vecReleaseListT;
        typedef std::map<int, BalEventCallbackWrapper> mapEventPoolT;

        struct BalEventReadyItem
        {
            int fd_;
            unsigned int read_:1;
            unsigned int write_:1;
            BalEventCallback callback_;
            mapEventPoolT::iterator iter_;
        };
        typedef std::vector<BalEventReadyItem> vecReadyPoolT;
    }
}
#endif
