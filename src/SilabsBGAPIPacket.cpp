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
 
#include "SilabsBGAPIProtocol.h"
#include "SilabsBGAPIPacket.h"

namespace Perilib
{

int8_t SilabsBGAPIPacket::prepareBufferAfterBuilding()
{
    PERILIB_DEBUG_PRINTLN("SilabsBGAPIPacket::prepareBufferAfterBuilding()");

    // make sure header and payload pointers are correct
    header = (header_t *)&buffer[0];
    payload = (payload_t *)&buffer[4];
    
    // update metadata
    SilabsBGAPIProtocol *bgapiProtocol = (SilabsBGAPIProtocol *)parserGenerator->protocolPtr;
    if (index > bgapiProtocol->maxResponseIndex)
    {
        // packet is event, not command/response
        messageType = 1;
    }
    payloadLength = bufferLength - 4;

    // fill BGAPI packet header data
    header->type = (messageType << 7) | (technologyType << 3) | (payloadLength >> 8);
    header->length = (payloadLength & 0xFF);
    header->groupId = definition[0];
    header->methodId = definition[1];
    return Result::OK;
}

} // namespace Perilib
