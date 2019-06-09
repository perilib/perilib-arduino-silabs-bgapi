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
 
#include "SilabsBGAPIProtocolWGM110.h"

namespace Perilib
{

const uint8_t SilabsBGAPIProtocolWGM110::commandTable[] =
{
    // {{ START perilib_protocol_cpp_packet_struct_set commands }}
    /* system_reset (ID=0/0) */
        /* group_id */      0x00,
        /* method_id */     0x00,
        /* outarg_count */  0x01,
        /* inarg_count */   0x80,
        /* cmda[0] */       UINT8,
        
    /* system_hello (ID=0/1) */
        /* group_id */      0x00,
        /* method_id */     0x01,
        /* outarg_count */  0x00,
        /* inarg_count */   0x00,
        
    /* system_whitelist_append (ID=0/10) */
        /* group_id */      0x00,
        /* method_id */     0x0A,
        /* outarg_count */  0x02,
        /* inarg_count */   0x01,
        /* cmda[0] */       MACADDR,
        /* cmda[1] */       UINT8,
        /* rspa[0] */       UINT16,
    // {{ END perilib_protocol_cpp_packet_struct_set commands }}
};

const uint8_t SilabsBGAPIProtocolWGM110::eventTable[] =
{
    // {{ START perilib_protocol_cpp_packet_struct_set events }}
    /* system_boot (ID=0/0) */
        /* group_id */      0x00,
        /* method_id */     0x00,
        /* inarg_count */   0x07,
        /* evta[0] */       UINT16, /* uint16 major */
        /* evta[1] */       UINT16, /* uint16 minor */
        /* evta[2] */       UINT16, /* uint16 patch */
        /* evta[3] */       UINT16, /* uint16 build */
        /* evta[4] */       UINT16, /* uint16 ll_version */
        /* evta[5] */       UINT8,  /* uint8 protocol_version */
        /* evta[6] */       UINT8,  /* uint8 hw */
    // {{ END perilib_protocol_cpp_packet_struct_set events }}
};

} // namespace Perilib
