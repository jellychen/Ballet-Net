
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <queue>
#include <stdarg.h>
#include <signal.h>

#include "LoTrace.h"
using namespace std;

bool _g_exitThread;
bool _g_exitThreadComplete;
pthread_t _g_writeThread;
static std::string _g_strTraceFile;
std::queue<std::string > _g_threadDataQeueu[2];
std::queue<std::string >* _g_threadDataQeueuIn;
std::queue<std::string >* _g_threadDataQeueuOut;
pthread_cond_t _g_threadDataQeueuCond_;
pthread_mutex_t _g_threadDataQeueuLocker;

bool LoWriteTraceFile(const char* str)
{
    if (!str) return false;
    std::ofstream ofs(_g_strTraceFile.c_str(), ios::app);
    if (!ofs.is_open()) return false;
    ofs << str << "\n";
    return true;
}

void* _threadWriteFunction(void*)
{
    while (true)
    {
        ::pthread_mutex_lock(&_g_threadDataQeueuLocker);
        ::pthread_cond_wait(&_g_threadDataQeueuCond_, &_g_threadDataQeueuLocker);
        std::queue<std::string >* temp = _g_threadDataQeueuIn;
        _g_threadDataQeueuIn = _g_threadDataQeueuOut;
        _g_threadDataQeueuOut = temp;
        ::pthread_mutex_unlock(&_g_threadDataQeueuLocker);

        std::ofstream ofs(_g_strTraceFile.c_str(), ios::app);
        if (ofs.is_open())
        {
            while (_g_threadDataQeueuOut->size() > 0)
            {
                std::string data = _g_threadDataQeueuOut->front();
                {
                    ofs << data.c_str() << "\n";
                }
                _g_threadDataQeueuOut->pop();
            }
        }

        if (_g_exitThread)
        {
            if (ofs.is_open())
            {
                while (_g_threadDataQeueuIn->size() > 0)
                {
                    std::string data = _g_threadDataQeueuIn->front();
                    ofs << data.c_str() << "\n";
                    _g_threadDataQeueuIn->pop();
                }
            }
            break;
        }
    }
    _g_exitThreadComplete = true;
    return 0;
}

bool Libs::Logger::LoTraceInit()
{
    _g_exitThread = false;
    _g_exitThreadComplete = false;
    _g_strTraceFile = ""; _g_writeThread = 0;
    _g_threadDataQeueuIn = _g_threadDataQeueu;
    _g_threadDataQeueuOut = _g_threadDataQeueu + 1;
    ::pthread_cond_init(&_g_threadDataQeueuCond_, 0);
    ::pthread_mutex_init(&_g_threadDataQeueuLocker, 0);
    return true;
}

bool Libs::Logger::LoTraceWaitClose(uint32_t timeout)
{
    _g_exitThread = true;
    const int timeinterval = 200;

    if (_g_writeThread)
    {
        int times = timeout / timeinterval;
        while (!_g_exitThreadComplete && times >= 0)
        {
            times--; usleep(timeinterval * 1000);
            ::pthread_cond_signal(&_g_threadDataQeueuCond_);
        }

        if (!_g_exitThreadComplete)
        {
            ::pthread_kill(_g_writeThread, 0);
        }
        ::pthread_join(_g_writeThread, 0);
    }
    ::pthread_cond_destroy(&_g_threadDataQeueuCond_);
    ::pthread_mutex_destroy(&_g_threadDataQeueuLocker);
    return true;
}

bool Libs::Logger::LoTraceFile(const char* name)
{
    if (!name) return false;
    _g_strTraceFile = name; return true;
}

bool Libs::Logger::LoTraceWriteThread()
{
    if (0 != _g_writeThread) return true;
    pthread_attr_t _attr; ::pthread_attr_init(&_attr);
    int ret = ::pthread_create(&_g_writeThread, &_attr, _threadWriteFunction, 0);
    ::pthread_attr_destroy(&_attr);
    return 0 == ret;
}

bool Libs::Logger::LoBaseTrace(const char* tag,
            const char* file, int line,  const char* fmt, ...)
{
    if (!tag || !fmt || !file) return false;

    const int maxBuffer = 2048;
    int offset = 0; char buffer[maxBuffer] = {0};
    struct timeval timeval; gettimeofday(&timeval, 0);
    strftime(buffer, maxBuffer, "%Y-%m-%d %T ", localtime(&timeval.tv_sec));
    sprintf(buffer + strlen(buffer), "【%s|%s:%d】", tag, file, line);
    offset = strlen(buffer);

    va_list args; va_start(args, fmt);
    vsprintf(buffer + offset, fmt, args); va_end(args);

    if (0 == _g_writeThread)
    {
        return LoWriteTraceFile(buffer);
    }
    else
    {
        ::pthread_mutex_lock(&_g_threadDataQeueuLocker);
        std::string data = buffer;
        _g_threadDataQeueuIn->push(data);
        ::pthread_cond_signal(&_g_threadDataQeueuCond_);
        ::pthread_mutex_unlock(&_g_threadDataQeueuLocker);
    }
}
