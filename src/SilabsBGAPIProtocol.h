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
    virtual int8_t getPacketFromNameAndArgs(StreamPacket *packet, const char *packetName, StreamParserGenerator *parserGenerator=0, ...);
    virtual int8_t getPacketDefinition(uint16_t index, const uint8_t **packetDef);
    virtual uint8_t getArgumentCount(uint16_t index, const uint8_t *packetDef);
    virtual const uint8_t *getFirstArgument(uint16_t index, const uint8_t *packetDef);
    virtual uint16_t getPayloadOffset(uint16_t index, const uint8_t *packetDef);

protected:
    const uint8_t *commandTable;
    const uint8_t *eventTable;
    const uint16_t maxCommandIndex;
    const uint16_t maxResponseIndex;
    const uint16_t maxEventIndex;
};

} // namespace Perilib

#endif /* __PERILIB_SILABSBGAPIPROTOCOL_H__ */
