#include "BalHttpParserCallback.h"
#include "BalHttpConnection.h"

namespace Ballet
{
    namespace Protocol
    {
        int __gOnHttpBegin(http_parser* parser)
        {
            if (!parser) return 0;
            BalHttpConnection* that = (BalHttpConnection*)(parser->data);
            return that->_OnHttpBegin(parser);
        }

        int __gOnUrlCallback(http_parser* parser, const char* buffer, size_t len)
        {
            if (!parser) return 0;
            BalHttpConnection* that = (BalHttpConnection*)(parser->data);
            return that->_OnUrlCallback(parser, buffer, len);
        }

        int __gOnHeaderField(http_parser* parser, const char* buffer, size_t len)
        {
            if (!parser) return 0;
            BalHttpConnection* that = (BalHttpConnection*)(parser->data);
            return that->_OnHeaderField(parser, buffer, len);
        }

        int __gOnHeaderValue(http_parser* parser, const char* buffer, size_t len)
        {
            if (!parser) return 0;
            BalHttpConnection* that = (BalHttpConnection*)(parser->data);
            return that->_OnHeaderValue(parser, buffer, len);
        }

        int __gOnHeaderComplete(http_parser* parser)
        {
            if (!parser) return 0;
            BalHttpConnection* that = (BalHttpConnection*)(parser->data);
            return that->_OnHeaderComplete(parser);
        }

        int __gOnStatus(http_parser* parser, const char* buffer, size_t len)
        {
            if (!parser) return 0;
            BalHttpConnection* that = (BalHttpConnection*)(parser->data);
            return that->_OnStatus(parser, buffer, len);
        }

        int __gOnContentBody(http_parser* parser, const char* buffer, size_t len)
        {
            if (!parser) return 0;
            BalHttpConnection* that = (BalHttpConnection*)(parser->data);
            return that->_OnContentBody(parser, buffer, len);
        }

        int __gOnHttpComplete(http_parser* parser)
        {
            if (!parser) return 0;
            BalHttpConnection* that = (BalHttpConnection*)(parser->data);
            return that->_OnHttpComplete(parser);
        }

        int __gOnChunkHeader(http_parser* parser)
        {
            if (!parser) return 0;
            BalHttpConnection* that = (BalHttpConnection*)(parser->data);
            return that->_OnChunkHeader(parser);
        }

        int __gOnChunkComplete(http_parser* parser)
        {
            if (!parser) return 0;
            BalHttpConnection* that = (BalHttpConnection*)(parser->data);
            return that->_OnChunkComplete(parser);
        }
    }
}
