#ifndef Libs_RapidXmlClosure_XmlClosure_H
#define Libs_RapidXmlClosure_XmlClosure_H
#include <Ballet/Common/BalInct.h>
#include <Libs/RapidXml/rapidxml.hpp>
using namespace Ballet;

namespace Libs
{
    class XmlClosure: public BalNoCoable
    {
    public:
        XmlClosure(const char* file, int max)
        {
            if (nullptr_() == file) return;
            if (max >= 10 * 1024 * 1024) return;

            std::ifstream fileStream(file);
            fileStream.seekg(0, std::ios::end);
            long fileSize = fileStream.tellg();
            do
            {
                if (fileSize > (long)max) break;
                char* fileBuffer = new(std::nothrow) char[fileSize];
                if (nullptr_() == fileBuffer) break;
                fileStream.seekg(0, std::ios::beg);
                fileStream.read(fileBuffer, fileSize);
                document_.parse<0>(fileBuffer);
                delete fileBuffer;
            }
            fileStream.close();
        }

    public:
        xml_node<>* RootNode() const
        {
            return document_.first_node();
        }

    public:
        xml_document<char> document_;
    };
}
#endif
