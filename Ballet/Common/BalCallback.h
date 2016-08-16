#ifndef Ballet_Common_BalCallback_H
#define Ballet_Common_BalCallback_H

namespace Ballet
{
    namespace Common
    {
        class BalCallback
        {
        public:
            virtual bool IsCallable() = 0;
        };
    }
}

#define BalCallbackSink(SinkName)                                               \
template <typename Host, typename Sink> class SinkName: public Sink             \
{

};
#endif
