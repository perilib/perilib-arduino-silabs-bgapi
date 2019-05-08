#ifndef __PERILIB_SILABSBGAPIPROTOCOLBLE1XX_H__
#define __PERILIB_SILABSBGAPIPROTOCOLBLE1XX_H__

#include <Perilib.h>

#include "SilabsBGAPIProtocol.h"

namespace Perilib
{
    
class SilabsBGAPIProtocolBLE1XX : public SilabsBGAPIProtocol
{
public:
    // {{ START perilib_protocol_cpp_index_enum_list }}
    enum packet_idx_t {
        BLE_IDX_CMD_SYSTEM_RESET,
        BLE_IDX_CMD_SYSTEM_HELLO,
        BLE_IDX_CMD_SYSTEM_WHITELIST_APPEND,
        BLE_IDX_CMD_MAX,
        
        BLE_IDX_RSP_SYSTEM_RESET,
        BLE_IDX_RSP_SYSTEM_HELLO,
        BLE_IDX_RSP_SYSTEM_WHITELIST_APPEND,
        BLE_IDX_RSP_MAX,
        
        BLE_IDX_EVT_SYSTEM_BOOT,
        BLE_IDX_EVT_MAX
    };
    // {{ END perilib_protocol_cpp_index_enum_list }}
    
    // {{ START perilib_protocol_cpp_packet_struct_set }}
    // {{ END perilib_protocol_cpp_packet_struct_set }}

    SilabsBGAPIProtocolBLE1XX()
            : SilabsBGAPIProtocol(commandTable, eventTable, BLE_IDX_CMD_MAX, BLE_IDX_RSP_MAX, BLE_IDX_EVT_MAX) { }

private:
    static const uint8_t commandTable[];
    static const uint8_t eventTable[];

};

} // namespace Perilib

#endif /* __PERILIB_SILABSBGAPIPROTOCOLBLE1XX_H__ */
