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
 
#ifndef __PERILIB_SILABSBGAPIDEVICEBGM1XX_H__
#define __PERILIB_SILABSBGAPIDEVICEBGM1XX_H__

#include <Perilib.h>

#include "SilabsBGAPIDevice.h"
#include "SilabsBGAPIProtocolBGM1XX.h"

#define SILABS_BGAPI_BGM1XX_MAX_RX_PACKET_SIZE 64
#define SILABS_BGAPI_BGM1XX_MAX_TX_PACKET_SIZE 64

namespace Perilib
{

class SilabsBGAPIDeviceBGM1XX : public SilabsBGAPIDevice
{
public:
    SilabsBGAPIDeviceBGM1XX(Stream *streamPtr)
            : SilabsBGAPIDevice(
                streamPtr,
                &protocol,
                &rxPacket,
                &txPacket),
              rxPacket(rxBuffer, sizeof(rxBuffer)),
              txPacket(txBuffer, sizeof(txBuffer))
       {
           rxPacket.technologyType = 0;
           txPacket.technologyType = 0;
       }
    
protected:
    uint8_t rxBuffer[SILABS_BGAPI_BGM1XX_MAX_RX_PACKET_SIZE];
    uint8_t txBuffer[SILABS_BGAPI_BGM1XX_MAX_TX_PACKET_SIZE];
    SilabsBGAPIPacket rxPacket;
    SilabsBGAPIPacket txPacket;
    SilabsBGAPIProtocolBGM1XX protocol;
};

} // namespace Perilib

#endif /* __PERILIB_SILABSBGAPIDEVICEBGM1XX_H__ */
