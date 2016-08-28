#include "BalServiceManage.h"
using namespace Ballet;
using namespace ServiceWorker;

namespace ServiceWorkerWatcher
{
    BalServiceManage* manageInstance = nullptr_();

    void SigHandler(int sig)
    {
        if (nullptr_() != manageInstance)
        {
            switch (sig)
            {
                case SIGINT:
                case SIGQUIT:
                case BALSINGLETON_EXIT:
                    manageInstance->Stop();
                    break;
                case SIGCHLD: break;
            }
        }
    }

    void installSigHandler()
    {
        ::signal(SIGINT,  SIG_IGN);
        ::signal(SIGHUP,  SIG_IGN);
        ::signal(SIGQUIT, SIG_IGN);
        ::signal(SIGPIPE, SIG_IGN);
        ::signal(SIGTTOU, SIG_IGN);
        ::signal(SIGTTIN, SIG_IGN);
        ::signal(SIGTERM, SIG_IGN);
        ::signal(SIGCHLD, SigHandler);
        ::signal(SIGQUIT, SigHandler);
        ::signal(SIGINT,  SigHandler);
        ::signal(BALSINGLETON_EXIT, SigHandler);
    }
}

BalServiceManage::BalServiceManage()
{
    ServiceWorkerWatcher::manageInstance = this;
}

BalServiceManage::~BalServiceManage()
{
    ServiceWorkerWatcher::manageInstance = nullptr_();
}

void BalServiceManage::Start(bool deamon)
{
    if (true == deamon)
    {
        if (::fork() > 0) return;
        ::setsid();
    }
    exit_ = false;
    ServiceWorkerWatcher::installSigHandler();

    servicePoolT::iterator iter = servicePool_.begin();
    while (servicePool_.end() != iter)
    {
        BalHandle<BalService> service = iter->second;
        if (service && service->ServiceAvailable())
        {
            uint32_t count = service->Count();
            for (uint32_t i = 0; i < count; ++i)
            {
                ForkService(service);
            }
        }
        ++iter;
    }

    while (true)
    {
        int status = 0;
        pid_t id = ::waitpid(-1, &status, WUNTRACED);
        FindServiceExit((long)id, !exit_);
        if (0 == serviceProcessPool_.size())
        {
            break;
        }
    }
}

bool BalServiceManage::AttachService(BalHandle<BalService> service)
{
    if (!service) return false;
    servicePool_[service.HashCode()] = service;
    return true;
}

bool BalServiceManage::DetachService(BalHandle<BalService> service)
{
    if (!service) return false;
    long hash = service.HashCode();
    servicePoolT::iterator iter = servicePool_.find(hash);
    if (servicePool_.end() == iter) return false;
    servicePool_.erase(iter);
    return true;
}

bool BalServiceManage::Stop()
{
    exit_ = true;
    servicePoolT::iterator iter = servicePool_.begin();
    for (; servicePool_.end() != iter; ++iter)
    {
        pid_t id = iter->first;
        ::kill(id, BALSINGLETON_EXIT);
    }
    return true;
}

bool BalServiceManage::FindServiceExit(long id, bool fork)
{
    servicePoolT::iterator iter = serviceProcessPool_.find(id);
    if (serviceProcessPool_.end() != iter)
    {
        BalHandle<BalService> service = iter->second;
        serviceProcessPool_.erase(iter);
        if (true == fork)
        {
            ForkService(service);
        }
    }
    return true;
}

bool BalServiceManage::ForkService(BalHandle<BalService> service)
{
    if (!service) return false;
    service->Start(); pid_t id = ::fork();

    if (id > 0)
    {
        serviceProcessPool_[(long)id] = service;
    }
    else if (0 == id)
    {
        ::signal(SIGINT,  SIG_IGN);
        ::signal(SIGHUP,  SIG_IGN);
        ::signal(SIGQUIT, SIG_IGN);
        ::signal(SIGPIPE, SIG_IGN);
        ::signal(SIGTTOU, SIG_IGN);
        ::signal(SIGTTIN, SIG_IGN);
        ::signal(SIGTERM, SIG_IGN);

        service->ServiceMain();
        ::exit(0);
    }
    return id >= 0;
}
