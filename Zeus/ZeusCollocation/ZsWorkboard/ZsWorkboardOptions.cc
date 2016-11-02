#include "ZsWorkboardOptions.h"
using namespace Zeus;
using namespace rapidxml;

ZsWorkboardOptions::ZsWorkboardOptions()
{
    netIpv6_ = false;
    netListenPort_ = 6801;
    maxTimeout_ = 30 * 1000;
    maxPackageSize_ = 30 * 1024;
    maxReadBufferSize_ = 1000 * 1024;
    maxWriteBufferSize_ = 1000 * 1024;
    maxHeartbeatTimeout_ = 30;
    minVoteElectionTimeout_ = 30;
    maxVoteElectionTimeout_ = 150;
}

void ZsWorkboardOptions::LoadOptions(const char* fileName)
{
    if (nullptr_() == fileName) return;
    std::ifstream fileStream(fileName);
    fileStream.seekg(0, std::ios::end);
    long fileSize = fileStream.tellg();

    do
    {
        if (!(fileSize > 0 && fileSize < 1000 * 1024)) break;
        char* fileBuffer = new(std::nothrow) char[fileSize];
        if (nullptr_() == fileBuffer) break;
        fileStream.seekg(0, std::ios::beg);
        fileStream.read(fileBuffer, fileSize);
        xml_document<char> doc; doc.parse<0>(fileBuffer);
        delete fileBuffer;
        xml_node<>* root = doc.first_node();
        if (nullptr_() == root) break;

        xml_node<>* node = nullptr_();

        node = root->first_node("net-ipv6");
        if (nullptr_() != node)
        {
            std::string value(node->value());
            StrTrim(value);
            if (0 == strcasecmp(value.c_str(), "true"))
            {
                netIpv6_ = true;
            }
        }

        node = root->first_node("net-listen-port");
        if (nullptr_() != node)
        {
            std::string value(node->value());
            StrTrim(value);
            int listenPort = atoi(value.c_str());
            if (listenPort > 0)
            {
                netListenPort_ = (uint16_t)(listenPort);
            }
        }

        node = root->first_node("net-tcp-timeout");
        if (nullptr_() != node)
        {
            std::string value(node->value());
            StrTrim(value);
            int timeout = atoi(value.c_str());
            if (timeout > 0)
            {
                maxTimeout_ = (uint32_t)(timeout);
            }
        }

        node = root->first_node("net-max-package-size");
        if (nullptr_() != node)
        {
            std::string value(node->value());
            StrTrim(value);
            int maxSize = atoi(value.c_str());
            if (maxSize > 0)
            {
                maxPackageSize_ = (uint32_t)(maxSize);
            }
        }

        node = root->first_node("net-max-read-buffer-size");
        if (nullptr_() != node)
        {
            std::string value(node->value());
            StrTrim(value);
            int maxSize = atoi(value.c_str());
            if (maxSize > 0)
            {
                maxReadBufferSize_ = (uint32_t)(maxSize);
            }
        }

        node = root->first_node("net-max-write-buffer-size");
        if (nullptr_() != node)
        {
            std::string value(node->value());
            StrTrim(value);
            int maxSize = atoi(value.c_str());
            if (maxSize > 0)
            {
                maxWriteBufferSize_ = (uint32_t)(maxSize);
            }
        }

        node = root->first_node("net-consistent-members");
        if (nullptr_() != node)
        {
            xml_node<>* childNode = node->first_node();
            for (; childNode; childNode = childNode->next_sibling())
            {
                if (0 == strcasecmp(childNode->name(), "member"))
                {
                    std::string value(childNode->value());
                    StrTrim(value);
                    consistentGroup_.push_back(value);
                }
            }
        }
    } while (0);
    fileStream.close();
}

uint32_t ZsWorkboardOptions::RandomVoteElectionTimeout() const
{
     srand((int)time(0));
     uint32_t range = maxVoteElectionTimeout_ - minVoteElectionTimeout_;
     return rand() %range + minVoteElectionTimeout_;
}
