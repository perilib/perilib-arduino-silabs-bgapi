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
 
#ifndef __PERILIB_SILABSBGAPIDEVICE_H__
#define __PERILIB_SILABSBGAPIDEVICE_H__

#include <Perilib.h>

#include "SilabsBGAPIProtocol.h"
#include "SilabsBGAPIPacket.h"

namespace Perilib
{

class SilabsBGAPIDevice : public StreamDevice
{
public:
    SilabsBGAPIDevice(
        ::Stream *arduinoUart,
        SilabsBGAPIProtocol *protocol,
        SilabsBGAPIPacket *lastRxPacket,
        SilabsBGAPIPacket *lastTxPacket)
            : StreamDevice(&stream),
              parserGenerator(protocol, lastRxPacket, lastTxPacket),
              stream(arduinoUart, &parserGenerator, this)
        {
            // set par/gen related stream object to self
            parserGenerator.streamPtr = (Stream *)&stream;
            
            // set default reset pin behavior (disabled, active-low, open-drain)
            resetPin = -1;
            resetPinAssertedState = LOW;
            resetPinAssertedMode = OUTPUT;
            resetPinDeassertedMode = INPUT;

            // set default wake-up pin behavior (disabled, active-high, push-pull)
            wakePin = -1;
            wakePinAssertedState = HIGH;
            wakePinAssertedMode = OUTPUT;
            wakePinDeassertedMode = OUTPUT;
        }
    
    virtual int8_t onPreTransmission();
    virtual void onPostTransmission();

    int8_t reset();
    
    StreamParserGenerator parserGenerator;
    UartStream stream;
    
    int8_t resetPin;
    uint8_t resetPinAssertedState;
    uint8_t resetPinAssertedMode;
    uint8_t resetPinDeassertedMode;
    
    int8_t wakePin;
    uint8_t wakePinAssertedState;
    uint8_t wakePinAssertedMode;
    uint8_t wakePinDeassertedMode;
};

} // namespace Perilib

#endif /* __PERILIB_SILABSBGAPIDEVICE_H__ */
