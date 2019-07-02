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
 
#ifndef __PERILIB_SILABSBGAPIPACKETBLE1XX_H__
#define __PERILIB_SILABSBGAPIPACKETBLE1XX_H__

#include <Perilib.h>

namespace Perilib
{

class SilabsBGAPIPacketBLE1XX : public SilabsBGAPIPacket
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
    
    SilabsBGAPIPacketBLE1XX(uint8_t *buffer, uint16_t bufferSize) :
            SilabsBGAPIPacket(buffer, bufferSize)
    {
        PERILIB_DEBUG_PRINTLN("SilabsBGAPIPacketBLE1XX::SilabsBGAPIPacketBLE1XX()");
        payload = (payload_t *)&buffer[4];
    }

    payload_t *payload;

};

} // namespace Perilib

#endif /* __PERILIB_SILABSBGAPIPACKETBLE1XX_H__ */
