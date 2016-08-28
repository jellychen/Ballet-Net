#ifndef Ballet_ServiceWorker_BalProcessCallback_H
#define Ballet_ServiceWorker_BalProcessCallback_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace ServiceWorker
    {
        class BalService;

        struct IBalServiceCallback :public BalCallback
        {
            virtual void OnStart(BalHandle<BalService>) =0;
            virtual void OnServiceMain(BalHandle<BalService>) =0;
        };

        BalCallbackSinkBegin(CBalServiceCallback)
        BalCallbackSink(void, OnStart, (BalHandle<BalService> service), (service))
        BalCallbackSink(void, OnServiceMain, (BalHandle<BalService> service), (service))
        BalCallbackSinkComplete()
        BalCallbackSinkPtrDefine(CBalServiceCallback, IBalServiceCallback)

        typedef BalHandle<IBalServiceCallback> BalServiceCallback;
    }
}
#endif
