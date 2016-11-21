#ifndef Ballet_Protocol_Http_BalHttpMime_H
#define Ballet_Protocol_Http_BalHttpMime_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace Protocol
    {
        class BalHttpMime: public BalNoCoable
        {
            typedef std::map<std::string, std::string> mapMimePoolT;
        public:
            BalHttpMime();

        public:
            static BalHttpMime& GetInstance()
            {
                static BalHttpMime _instance;
                return _instance;
            }

        public:
            std::string GetMime(const char*) const;

        private:
            mapMimePoolT mimePool_;
        };
    }
}
#endif//Ballet_Protocol_Http_BalHttpMime_H
