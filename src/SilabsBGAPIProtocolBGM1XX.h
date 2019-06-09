/**
 * Perilib Peripheral Device Library
 * Copyright (c) 2019 Jeff Rowberg
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software 
 * without restriction, including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons
 * to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
 
#ifndef __PERILIB_SILABSBGAPIPROTOCOLBGM1XX_H__
#define __PERILIB_SILABSBGAPIPROTOCOLBGM1XX_H__

#include <Perilib.h>

#include "SilabsBGAPIProtocol.h"

namespace Perilib
{
    
class SilabsBGAPIProtocolBGM1XX : public SilabsBGAPIProtocol
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

    SilabsBGAPIProtocolBGM1XX()
            : SilabsBGAPIProtocol(commandTable, eventTable, BLE_CMD_MAX, BLE_RSP_MAX, BLE_EVT_MAX) { }

private:
    static const uint8_t commandTable[];
    static const uint8_t eventTable[];

};

} // namespace Perilib

#endif /* __PERILIB_SILABSBGAPIPROTOCOLBGM1XX_H__ */
