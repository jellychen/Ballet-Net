#ifndef Ballet_Protocol_Http_BalHttpParserCallback_H
#define Ballet_Protocol_Http_BalHttpParserCallback_H
#include "Common/BalInct.h"
#include "http_parser.h"

namespace Ballet
{
    namespace Protocol
    {
        int __gOnHttpBegin      (http_parser* parser);
        int __gOnUrlCallback    (http_parser* parser, const char* buffer, size_t len);
        int __gOnHeaderField    (http_parser* parser, const char* buffer, size_t len);
        int __gOnHeaderValue    (http_parser* parser, const char* buffer, size_t len);
        int __gOnHeaderComplete (http_parser* parser);
        int __gOnStatus         (http_parser* parser, const char* buffer, size_t len);
        int __gOnContentBody    (http_parser* parser, const char* buffer, size_t len);
        int __gOnHttpComplete   (http_parser* parser);
        int __gOnChunkHeader    (http_parser* parser);
        int __gOnChunkComplete  (http_parser* parser);
    }
}
#endif//Ballet_Protocol_Http_BalHttpParserCallback_H
