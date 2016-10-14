#ifndef Ballet_BootUtil_BalSerializeNumber_H
#define Ballet_BootUtil_BalSerializeNumber_H
#include "Common/BalInct.h"
#include "BalEndian.h"

namespace Ballet
{
    namespace BootUtil
    {
        template<typename T> struct BalNumberObject_T
        {
            T rawData_;
            typedef BalNumberObject_T tClass;
            static const uint32_t rawDataSize_ = sizeof(T);
            BalNumberObject_T():rawData_(0){}
            BalNumberObject_T(T data):rawData_(data){}
            BalNumberObject_T(const tClass& object):rawData_(object.rawData_){}

            operator T() const{return rawData_;}
            T* operator&() const {return &rawData_;}
            tClass& operator=(T data){rawData_ = data; return *this;}
            tClass& operator=(const tClass& object){rawData_ = object.rawData_; return *this;}

            inline int Size() {return sizeof(T);}
            inline int Serialize(std::string& str, bool endian)
            {
                if (endian)
                {
                    T data = htoni(rawData_);
                    str.append((char*)(&data), sizeof(T));
                }
                else
                {
                    str.append((char*)(&rawData_), sizeof(T));
                }
                return sizeof(T);
            }

            inline int Serialize(char* buffer, uint32_t capacity, bool endian)
            {
                if (!buffer || capacity < sizeof(T)) return -1;
                if (endian)
                {
                    T data = htoni(rawData_);
                    *((T*)(buffer)) = data;
                }
                else
                {
                    *((T*)(buffer)) = rawData_;
                }
                return sizeof(T);
            }

            inline int UnSerialize(char* buffer, uint32_t capacity, bool endian)
            {
                if (!buffer || capacity < sizeof(T)) return -1;
                if (endian)
                {
                    T data = *((T*)(buffer));
                    rawData_ = ntohi(data);
                }
                else
                {
                    rawData_ = *((T*)(buffer));
                }
                return sizeof(T);
            }
        };

        typedef BalNumberObject_T<int8_t>   BalPackInt8;
        typedef BalNumberObject_T<uint8_t>  BalPackUInt8;
        typedef BalNumberObject_T<int16_t>  BalPackInt16;
        typedef BalNumberObject_T<uint16_t> BalPackUInt16;
        typedef BalNumberObject_T<int32_t>  BalPackInt32;
        typedef BalNumberObject_T<uint32_t> BalPackUInt32;
        typedef BalNumberObject_T<int64_t>  BalPackInt64;
        typedef BalNumberObject_T<uint64_t> BalPackUInt64;
    }
}
#endif
