#ifndef __PERILIB_SILABSBGAPIPACKET_H__
#define __PERILIB_SILABSBGAPIPACKET_H__

#include <Perilib.h>

namespace Perilib
{

class SilabsBGAPIPacket : public StreamPacket
{
public:
    typedef struct {
        uint16_t major;
        uint16_t minor;
        uint16_t patch;
        uint16_t build;
        uint16_t ll_version;
        uint8_t protocol_version;
        uint8_t hw;
    } __attribute__((packed)) ble_evt_system_boot_t;

    typedef union {
        ble_evt_system_boot_t ble_evt_system_boot;
    } payload_t;
    
    typedef struct {
        uint8_t type;
        uint8_t length;
        uint8_t groupId;
        uint8_t methodId;
    } __attribute__((packed)) header_t;
    
    inline uint16_t getPayloadLength() { return header ? (header->length + ((uint16_t)(header->type & 0x07) << 8)) : 0; }

    header_t *header;
    payload_t *payload;

};

} // namespace Perilib

#endif /* __PERILIB_SILABSBGAPIPACKET_H__ */
