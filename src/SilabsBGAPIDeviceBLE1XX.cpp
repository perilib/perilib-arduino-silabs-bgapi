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
 
#include "SilabsBGAPIDeviceBLE1XX.h"

namespace Perilib
{

int8_t SilabsBGAPIDeviceBLE1XX::onPreTransmission()
{
    PERILIB_DEBUG_PRINTLN("SilabsBGAPIDeviceBLE1XX::onPreTransmission()");

    if (wakePin != -1)
    {
        // assert module wake-up pin
        digitalWrite(wakePin, wakeAssertedState ? HIGH : LOW);
    }
    
    if (packetMode)
    {
        // prefix the transmission with a <length> byte
        // so module DMA can allocate and process faster
        streamPtr->write((uint8_t *)&streamPtr->parserGeneratorPtr->lastTxPacketPtr->bufferLength, 1);
    }
    
    // allow transmission
    return 0;
}

void SilabsBGAPIDeviceBLE1XX::onPostTransmission()
{
    PERILIB_DEBUG_PRINTLN("SilabsBGAPIDeviceBLE1XX::onPostTransmission()");
    
    if (wakePin != -1)
    {
        // de-assert module wake-up pin
        digitalWrite(wakePin, wakeAssertedState ? LOW : HIGH);
    }
}

} // namespace Perilib
