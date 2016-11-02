#ifndef Ballet_LoTrace_LoTrace_H
#define Ballet_LoTrace_LoTrace_H
namespace Libs
{
    namespace Logger
    {
        bool LoTraceInit();
        bool LoTraceWaitClose(uint32_t);
        bool LoTraceFile(const char* name);
        bool LoTraceWriteThread();
        bool LoBaseTrace(const char* tag,
            const char* file, int line,  const char* fmt, ...);
    }
}

#define __LOG__(tag, fmt, args...)                                              \
    Libs::Logger::LoBaseTrace(#tag, __FILE__, __LINE__, fmt, ##args);
#define __LOG_DEBUG__(fmt, args...)                                             \
    Libs::Logger::LoBaseTrace("DEBUG", __FILE__, __LINE__, fmt, ##args);
#define __LOG_INFO__(fmt, args...)                                              \
    Libs::Logger::LoBaseTrace("INFO", __FILE__, __LINE__, fmt, ##args);
#define __LOG_WARNING__(fmt, args...)                                           \
    Libs::Logger::LoBaseTrace("WARNING", __FILE__, __LINE__, fmt, ##args);
#define __LOG_FATAL__(fmt, args...)                                             \
    Libs::Logger::LoBaseTrace("FATAL", __FILE__, __LINE__, fmt, ##args);

#endif
