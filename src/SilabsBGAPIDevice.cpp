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
 
#include "SilabsBGAPIDevice.h"

namespace Perilib
{

int8_t SilabsBGAPIDevice::onPreTransmission()
{
    PERILIB_DEBUG_PRINTLN("SilabsBGAPIDevice::onPreTransmission()");

    if (wakePin != -1)
    {
        // assert module wake-up pin
        pinMode(wakePin, wakePinAssertedMode);
        digitalWrite(wakePin, wakePinAssertedState ? HIGH : LOW);
    }
    
    // allow transmission
    return 0;
}

void SilabsBGAPIDevice::onPostTransmission()
{
    PERILIB_DEBUG_PRINTLN("SilabsBGAPIDevice::onPostTransmission()");
    
    if (wakePin != -1)
    {
        // de-assert module wake-up pin
        pinMode(wakePin, wakePinDeassertedMode);
        digitalWrite(wakePin, wakePinAssertedState ? LOW : HIGH);
    }
}

int8_t SilabsBGAPIDevice::reset()
{
    PERILIB_DEBUG_PRINTLN("SilabsBGAPIDevice::reset()");

    if (resetPin != -1)
    {
        // assert module reset pin
        pinMode(resetPin, resetPinAssertedMode);
        digitalWrite(resetPin, resetPinAssertedState ? HIGH : LOW);
        
        // wait a moment
        delay(5);
        
        // de-assert module reset pin
        pinMode(resetPin, resetPinDeassertedMode);
        digitalWrite(resetPin, resetPinAssertedState ? LOW : HIGH);
    }
    
    // allow transmission
    return 0;
}

} // namespace Perilib
