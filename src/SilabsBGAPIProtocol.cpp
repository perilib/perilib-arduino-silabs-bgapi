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

int8_t SilabsBGAPIProtocol::testPacketComplete(const uint8_t *buffer, uint16_t length, StreamParserGenerator *parserGenerator, bool isTx)
{
    // suppress unused parameter warnings
    (void)parserGenerator;
    (void)isTx;

    PERILIB_DEBUG_PRINT("SilabsBGAPIProtocol::testPacketComplete([...], ");
    PERILIB_DEBUG_PRINT(length);
    PERILIB_DEBUG_PRINTLN(", ...)");

    // make sure we have at least the header (4 bytes)
    if (length > 3)
    {
        // check 11-bit "length" field in 4-byte header
        uint16_t payloadLength = ((buffer[0] & 0x03) << 8) + buffer[1];
        if (length == (payloadLength + 4))
        {
            // existing buffer plus new byte is expected length
            return ParseStatus::COMPLETE;
        }
    }

    // not finished if we made it here
    return ParseStatus::IN_PROGRESS;
}

int8_t SilabsBGAPIProtocol::getPacketFromBuffer(StreamPacket *packet, uint8_t *buffer, uint16_t length, StreamParserGenerator *parserGenerator, bool isTx)
{
    // suppress unused parameter warnings
    (void)parserGenerator;

    PERILIB_DEBUG_PRINT("SilabsBGAPIProtocol::getPacketFromBuffer(*{}, [...], ");
    PERILIB_DEBUG_PRINT(length);
    PERILIB_DEBUG_PRINTLN(", ...)");

    // ensure packet and buffer pointers are valid
    if (!packet || !buffer) return Result::NULL_POINTER;
    
    // assign special metadata
    SilabsBGAPIPacket *bgapiPacket = (SilabsBGAPIPacket *)packet;
    bgapiPacket->messageType = (buffer[0] >> 7);
    bgapiPacket->technologyType = (buffer[0] >> 3) & 0xF;
    bgapiPacket->payloadLength = ((buffer[0] & 0x7) << 8) | buffer[1];
    
    // get packet definition
    return getPacketDefinitionFromBuffer(buffer, length, isTx, &packet->index, &packet->definition);
}

int8_t SilabsBGAPIProtocol::getPacketFromIndexAndArgs(StreamPacket *packet, uint16_t index, va_list argv, StreamParserGenerator *parserGenerator)
{
    // run base class implementation first
    StreamProtocol::getPacketFromIndexAndArgs(packet, index, argv, parserGenerator);
    
    // get pointer to child class instance
    SilabsBGAPIPacket *bgapiPacket = (SilabsBGAPIPacket *)packet;

    // update metadata
    if (index > maxResponseIndex)
    {
        // packet is event, not command/response
        bgapiPacket->messageType = 1;
    }
    bgapiPacket->payloadLength = packet->bufferLength - 4;

    // fill BGAPI packet header data
    bgapiPacket->header->type = (bgapiPacket->messageType << 7) | (bgapiPacket->technologyType << 3) | (bgapiPacket->payloadLength >> 8);
    bgapiPacket->header->length = (bgapiPacket->payloadLength & 0xFF);
    bgapiPacket->header->groupId = packet->definition[0];
    bgapiPacket->header->methodId = packet->definition[1];
    
    return Result::OK;
}

int8_t SilabsBGAPIProtocol::getPacketDefinitionFromIndex(uint16_t index, const uint8_t **packetDef)
{
    PERILIB_DEBUG_PRINT("SilabsBGAPIProtocol::getPacketDefinitionFromIndex(");
    PERILIB_DEBUG_PRINT(index);
    PERILIB_DEBUG_PRINTLN(", ...)");

    // ensure destination pointer is valid
    if (!packetDef) return Result::NULL_POINTER;
    
    // determine correct look-up table and search range, assume commands
    // (table 0 is commands, table 1 is responses, table 2 is events)
    const uint8_t *search = commandTable;
    uint16_t max = maxCommandIndex;
    uint8_t table = 0;
    if (index > maxResponseIndex)
    {
        // switch to event table
        search = eventTable;
        index -= (maxResponseIndex + 1);
        max = maxEventIndex - (maxResponseIndex + 1);
        table = 2;
    }
    else if (index > maxCommandIndex)
    {
        // switch to response table (same as command but with index offsets)
        index -= (maxCommandIndex + 1);
        max = maxResponseIndex - (maxCommandIndex + 1);
        table = 1;
    }
    
    // abort if requested packet is out of range
    if (index >= max) return Result::INVALID_INDEX;
    
    // jump through [index] definitions to obtain requested entry
    uint16_t i;
    for (i = 0; i < index; i++)
    {
        if (table == 0 || table == 1)
        {
            // 4 bytes fixed definition size + [out] command args, [in] response args (8th bit masked)
            search += 4 + search[2] + (search[3] & 0x7F);
        }
        else
        {
            // 3 bytes fixed definition size + [in] event args
            search += 3 + search[2];
        }
    }
    
    // assign definition pointer and return success
    *packetDef = search;
    return Result::OK;
}

int8_t SilabsBGAPIProtocol::getPacketDefinitionFromBuffer(const uint8_t *buffer, uint16_t length, bool isTx, uint16_t *index, const uint8_t **packetDef)
{
    // suppress unused parameter warnings
    (void)length;

    PERILIB_DEBUG_PRINTLN("SilabsBGAPIProtocol::getPacketDefinitionFromBuffer(...)");

    // ensure destination pointer is valid
    if (!buffer || !index || !packetDef) return Result::NULL_POINTER;

    // identify packet, assume response (RX)
    uint16_t i;
    const uint8_t *search = commandTable;
    uint16_t maxIndex = maxResponseIndex;
    uint16_t indexOffset = maxCommandIndex + 1;
    if ((buffer[0] & 0x80) != 0)
    {
        // buffer contains event packet (RX)
        search = eventTable;
        maxIndex = maxEventIndex;
        indexOffset = maxResponseIndex + 1;
    }
    else if (isTx)
    {
        // buffer contains command packet (TX), less common for buffer analysis
        maxIndex = maxCommandIndex;
        indexOffset = 0;
    }
    
    // search through table
    for (i = 0; i < maxIndex; i++)
    {
        // check for match
        if (search[0] == buffer[2] && search[1] == buffer[3])
        {
            // group/method match, so stop searching
            break;
        }

        if ((buffer[0] & 0x80) == 0)
        {
            // jump to next command definition
            search += search[2] + (search[3] & 0x7F) + 4;
        }
        else
        {
            // jump to next event definition
            search += search[2] + 3;
        }
    }
    
    // if we didn't couldn't identify the packet, stop here
    if (i == maxIndex) return Result::UNKNOWN_PACKET;

    // assign index/definition pointers and return success
    *index = i + indexOffset;
    *packetDef = search;
    return Result::OK;
}

uint8_t SilabsBGAPIProtocol::getArgumentCount(uint16_t index, const uint8_t *packetDef)
{
    PERILIB_DEBUG_PRINT("SilabsBGAPIProtocol::getArgumentCount(");
    PERILIB_DEBUG_PRINT(index);
    PERILIB_DEBUG_PRINTLN(", ...)");

    if (!packetDef) return 0;
    if (index < maxCommandIndex || index > maxResponseIndex)
    {
        // outgoing command or incoming event arguments
        return packetDef[2];
    }

    // incoming response arguments
    return packetDef[3];
}

const uint8_t *SilabsBGAPIProtocol::getFirstArgument(uint16_t index, const uint8_t *packetDef)
{
    PERILIB_DEBUG_PRINT("SilabsBGAPIProtocol::getFirstArgument(");
    PERILIB_DEBUG_PRINT(index);
    PERILIB_DEBUG_PRINTLN(", ...)");

    if (!packetDef) return 0;
    if (index < maxCommandIndex)
    {
        // command (found in command table, 1st half of each packet definition)
        return &packetDef[4];
    }
    else if (index < maxResponseIndex)
    {
        // response (found in command table, 2nd half of each packet definition)
        return &packetDef[4 + packetDef[2]];
    }
    
    // event (found in event table)
    return &packetDef[3];
}

uint16_t SilabsBGAPIProtocol::getPayloadOffset(uint16_t index, const uint8_t *packetDef)
{
    // suppress unused parameter warnings
    (void)index;
    (void)packetDef;

    PERILIB_DEBUG_PRINT("SilabsBGAPIProtocol::getPayloadOffset(");
    PERILIB_DEBUG_PRINT(index);
    PERILIB_DEBUG_PRINTLN(", ...)");

    // payload is always 4 bytes into the complete packet buffer
    return 4;
}

} // namespace Perilib
