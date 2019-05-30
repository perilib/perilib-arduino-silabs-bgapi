#ifndef __PERILIB_SILABSBGAPIPROTOCOLWF121_H__
#define __PERILIB_SILABSBGAPIPROTOCOLWF121_H__

#include <Perilib.h>

#include "SilabsBGAPIProtocol.h"

namespace Perilib
{
    
class SilabsBGAPIProtocolWF121: public SilabsBGAPIProtocol
{
public:
    // {{ START perilib_protocol_cpp_index_enum_list }}
    enum packet_idx_t {
        BLE_CMD_SYSTEM_RESET,
        BLE_CMD_SYSTEM_HELLO,
        BLE_CMD_SYSTEM_WHITELIST_APPEND,
        BLE_CMD_MAX,
        
        BLE_RSP_SYSTEM_RESET,
        BLE_RSP_SYSTEM_HELLO,
        BLE_RSP_SYSTEM_WHITELIST_APPEND,
        BLE_RSP_MAX,
        
        BLE_EVT_SYSTEM_BOOT,
        BLE_EVT_MAX
    };
    // {{ END perilib_protocol_cpp_index_enum_list }}
    
    // {{ START perilib_protocol_cpp_packet_struct_set }}
    // {{ END perilib_protocol_cpp_packet_struct_set }}

    SilabsBGAPIProtocolWF121()
            : SilabsBGAPIProtocol(commandTable, eventTable, BLE_CMD_MAX, BLE_RSP_MAX, BLE_EVT_MAX) { }

private:
    static const uint8_t commandTable[];
    static const uint8_t eventTable[];

};

} // namespace Perilib

#endif /* __PERILIB_SILABSBGAPIPROTOCOLWF121_H__ */
