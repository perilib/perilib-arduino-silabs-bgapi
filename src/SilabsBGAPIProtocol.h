/**
 * Perilib Peripheral Device Library
 * Copyright (c) Jeff Rowberg
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
 
#ifndef __PERILIB_SILABSBGAPIPROTOCOL_H__
#define __PERILIB_SILABSBGAPIPROTOCOL_H__

#include <Perilib.h>

namespace Perilib
{
    
class SilabsBGAPIProtocol : public StreamProtocol
{
public:
    SilabsBGAPIProtocol(
        const uint8_t *commandTable,
        const uint8_t *eventTable,
        uint16_t maxCommandIndex,
        uint16_t maxResponseIndex,
        uint16_t maxEventIndex)
            : commandTable(commandTable),
              eventTable(eventTable),
              maxCommandIndex(maxCommandIndex),
              maxResponseIndex(maxResponseIndex),
              maxEventIndex(maxEventIndex)
    {
        incomingPacketTimeoutMs = 500;
        responsePacketTimeoutMs = 1200;
    }
    
    virtual int8_t testPacketComplete(const uint8_t *buffer, uint16_t length, StreamParserGenerator *parserGenerator=0, bool isTx=false);
    virtual int8_t getPacketFromBuffer(StreamPacket *packet, uint8_t *buffer, uint16_t length, StreamParserGenerator *parserGenerator=0, bool isTx=false);
    virtual int8_t getPacketDefinitionFromIndex(uint16_t index, const uint8_t **packetDef);
    virtual int8_t getPacketDefinitionFromBuffer(const uint8_t *buffer, uint16_t length, uint16_t *index, const uint8_t **packetDef);
    virtual uint8_t getArgumentCount(uint16_t index, const uint8_t *packetDef);
    virtual const uint8_t *getFirstArgument(uint16_t index, const uint8_t *packetDef);
    virtual uint16_t getPayloadOffset(uint16_t index, const uint8_t *packetDef);

    const uint8_t *commandTable;
    const uint8_t *eventTable;
    const uint16_t maxCommandIndex;
    const uint16_t maxResponseIndex;
    const uint16_t maxEventIndex;
};

} // namespace Perilib

#endif /* __PERILIB_SILABSBGAPIPROTOCOL_H__ */
