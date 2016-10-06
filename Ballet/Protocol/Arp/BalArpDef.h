#ifndef Ballet_Protocol_Arp_BalArpDef_H
#define Ballet_Protocol_Arp_BalArpDef_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace Protocol
    {
        #pragma pack(1)

        struct ethernet_head
        {
            uint8_t dest_mac[6];            // 接收方MAC地址
            uint8_t source_mac[6];          // 发送方MAC地址
            uint16_t ethernet_type;         // ethernet_type
        };

        struct arp_head
        {
            uint16_t hardware_type;         // 硬件类型
            uint16_t protocol_type;         // 上层协议类型
            uint8_t addr_len;               // MAC地址长度
            uint8_t protocol_len;           // IP地址长度
            uint16_t option_code;           // 操作码
            uint8_t source_mac[6];          // 发送方MAC
            uint8_t source_ip[4];           // 发送方IP
            uint8_t dest_mac[6];            // 接收方MAC
            uint8_t dest_ip[4];             // 接收方IP
            uint8_t padding[18];            // 填充数据
        };

        struct arp_packet
        {
            ethernet_head eth;
            arp_head arp;
        };

        #pragma pack()
    }
}
#endif//Ballet_Protocol_Arp_BalArpDef_H
