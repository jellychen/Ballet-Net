#ifndef Ballet_Protocol_Http_BalHttpConnection_H
#define Ballet_Protocol_Http_BalHttpConnection_H
#include "Common/BalInct.h"
#include "Network/BalTcpConnection.h"
#include "http_parser.h"

namespace Ballet
{
    using namespace Network;
    namespace Protocol
    {
        enum BalHttpMethod
        {
            HttpUnknown, HttpDelete, HttpGet, HttpHead, HttpPost, HttpPut,
        };

        class BalHttpServer;
        class BalHttpConnection :public BalElement,
            public BalTcpSocket, public BalShareThis
        {
        public:
            BalHttpConnection(int id, BalHandle<BalHttpServer> server);
            virtual ~BalHttpConnection();

        public:
            bool IsV6();
            bool Close(bool now);
            bool ShutdownWrite();
            uint32_t TimeoutTime() const;
            uint32_t MaxWriteBufferSize() const;
            BalConnStatusEnum GetStatus() const;
            BalHandle<BalInetAddress> GetPeer() const;
            BalHandle<BalInetAddress> GetLocal() const;

        public:
            BalHttpMethod GetHttpMethod() const;
            void GetHttpUrl(std::string*) const;
            void GetHttpVersion(int*, int*) const;
            void GetHttpHeaderField(const char*, std::string*) const;
            bool GetKeepAlive() const;

        public:
            void RespondBegin();
            void RespondVersion(int, int);
            void RespondKeepAlive();
            void RespondChunked();
            void RespondStatus(int, const char*);
            void RespondContentType(const char*);
            void RespondContentLength(int);
            void RespondHeader(const char*, const char*);
            void RespondHeaderComplete(bool);
            void RespondBody(const char*, int);
            void RespondChunk(const char*, int);
            void RespondChunkComplete();
            void RespondComplete(bool);
            void RespondData(const char*, int, bool, bool);

        protected:
            bool WriteRawBuffer(const char* buffer, uint32_t size);
            bool DoCloseProcedure(bool accord, bool delEvent);
            void OnTime(uint32_t id, BalHandle<BalTimer> timer);
            uint32_t DoHttpParser(const char* buffer, uint32_t len);

        public:
            virtual BalEventCallbackEnum ShouldRead(int id, BalHandle<BalEventLoop> el);
            virtual BalEventCallbackEnum ShouldWrite(int id, BalHandle<BalEventLoop> el);

        public:
            int _OnHttpBegin        (http_parser* parser);
            int _OnUrlCallback      (http_parser* parser, const char* buffer, size_t len);
            int _OnHeaderField      (http_parser* parser, const char* buffer, size_t len);
            int _OnHeaderValue      (http_parser* parser, const char* buffer, size_t len);
            int _OnHeaderComplete   (http_parser* parser);
            int _OnStatus           (http_parser* parser, const char* buffer, size_t len);
            int _OnContentBody      (http_parser* parser, const char* buffer, size_t len);
            int _OnHttpComplete     (http_parser* parser);
            int _OnChunkHeader      (http_parser* parser);
            int _OnChunkComplete    (http_parser* parser);

        protected:
            BalConnStatusEnum status_;
            BalEventHandle eventHandle_;
            http_parser request_parser_;
            http_parser_settings request_setting_;
            BalWeakHandle<BalHttpServer> httpServer_;
            CBalTimerCallbackPtr<BalHttpConnection> timerCallbackPtr_;
            CBalEventCallbackPtr<BalHttpConnection> eventCallbackPtr_;
            int64_t lastReadTime_; BalBufferStream writeBuffer_;

            typedef std::map<std::string, std::string> mapPoolT;
            http_parser requestParser_;
            http_parser_settings requestSetting_;
            std::string requestUrl_;
            mapPoolT requestHeaderField_;
            uint32_t requestBodySize_;
            uint32_t currentChunkedSize_;
            bool requestKeepAlive_;
            std::string requestHeaderFieldKey_;
            std::string requestHeaderFieldValue_;
            BalBufferStream requestBuffer_;

            bool respondKeepAlive_;
            bool respondChunked_;
            std::string respondHttpHeadBuffer_;
            BalBufferStream respondBuffer_;
        };
    }
}
#endif//Ballet_Protocol_Http_BalHttpServer_H
