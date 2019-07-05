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
 
#ifndef __PERILIB_SILABSBGAPIDEVICEBLE1XX_H__
#define __PERILIB_SILABSBGAPIDEVICEBLE1XX_H__

#include <Perilib.h>

#include "SilabsBGAPIDevice.h"
#include "SilabsBGAPIProtocolBLE1XX.h"
#include "SilabsBGAPIPacketBLE1XX.h"

#define SILABS_BGAPI_BLE1XX_MAX_RX_PACKET_SIZE 64
#define SILABS_BGAPI_BLE1XX_MAX_TX_PACKET_SIZE 64

namespace Perilib
{

class SilabsBGAPIDeviceBLE1XX : public SilabsBGAPIDevice
{
public:
    SilabsBGAPIDeviceBLE1XX(::Stream *arduinoUart)
            : SilabsBGAPIDevice(
                arduinoUart,
                &protocol,
                &lastRxPacket,
                &lastTxPacket),
              lastRxPacket(rxBuffer, sizeof(rxBuffer)),
              lastTxPacket(txBuffer, sizeof(txBuffer))
       {
           lastRxPacket.technologyType = 0;
           lastTxPacket.technologyType = 0;
           packetMode = false;
       }
       
    virtual int8_t onPreTransmission();
       
    bool packetMode;
    
protected:
    uint8_t rxBuffer[SILABS_BGAPI_BLE1XX_MAX_RX_PACKET_SIZE];
    uint8_t txBuffer[SILABS_BGAPI_BLE1XX_MAX_TX_PACKET_SIZE];
    SilabsBGAPIPacketBLE1XX lastRxPacket;
    SilabsBGAPIPacketBLE1XX lastTxPacket;
    SilabsBGAPIProtocolBLE1XX protocol;
};

} // namespace Perilib

#endif /* __PERILIB_SILABSBGAPIDEVICEBLE1XX_H__ */
