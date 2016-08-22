#ifndef Ballet_BootUtil_BalSerialize_H
#define Ballet_BootUtil_BalSerialize_H
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

            inline uint32_t Size() {return sizeof(T);}
            inline uint32_t Serialize(std::string& str, bool endian)
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

            inline uint32_t Serialize(char* buffer, uint32_t& capacity, bool endian)
            {
                if (!buffer || capacity < sizeof(T)) return 0;
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

            inline uint32_t UnSerialize(char* buffer, uint32_t& capacity, bool endian)
            {
                if (!buffer || capacity < sizeof(T)) return 0;
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

        typedef BalNumberObject_T<int8_t>   BalSerializeInt8;
        typedef BalNumberObject_T<uint8_t>  BalSerializeUInt8;
        typedef BalNumberObject_T<int16_t>  BalSerializeInt16;
        typedef BalNumberObject_T<uint16_t> BalSerializeUInt16;
        typedef BalNumberObject_T<int32_t>  BalSerializeInt32;
        typedef BalNumberObject_T<uint32_t> BalSerializeUInt32;
        typedef BalNumberObject_T<int64_t>  BalSerializeInt64;
        typedef BalNumberObject_T<uint64_t> BalSerializeUInt64;
    }
}
#endif
