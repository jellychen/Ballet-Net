#ifndef Ballet_Protocol_Arp_BalArpDef_H
#define Ballet_Protocol_Arp_BalArpDef_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace Protocol
    {
        #pragma pack(1)
        struct ArpPackDataDef
        {
            unsigned short sHardType;      //硬件类型
            unsigned short sProtocolType;  //协议类型
            unsigned char cHardAddrLen;    //硬件地址长度
            unsigned char cIpAddrLen;      //映射的协议地址长度
            unsigned short sOpType;        //操作类型

            unsigned char aSendMac[6];     //发送者MAC地址
            unsigned char aSendIP[4];      //发送者IP地址
            unsigned char aDstMac[6];      //目的地MAC地址
            unsigned char aDstIP[4];       //目的地IP地址
        };
        #pragma pack()
    }
}
#endif//Ballet_Protocol_Arp_BalArpDef_H
