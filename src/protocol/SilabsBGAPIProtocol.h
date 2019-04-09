#ifndef __PERILIB_PROTOCOL_SILABSBGAPIPROTOCOL_H__
#define __PERILIB_PROTOCOL_SILABSBGAPIPROTOCOL_H__

#include <Perilib.h>

namespace Perilib
{
    
class SilabsBGAPIProtocol : public StreamProtocol
{
public:
    SilabsBGAPIProtocol();
    virtual int8_t testPacketComplete(const uint8_t *buffer, uint16_t length, uint8_t newByte, StreamParserGenerator *parserGenerator=0, bool isTx=false);
    virtual int8_t getPacketFromBuffer(StreamPacket *packet, const uint8_t *buffer, uint16_t length, StreamParserGenerator *parserGenerator=0, bool isTx=false);
    virtual int8_t getPacketFromNameAndArgs(StreamPacket *packet, const char *packetName, StreamParserGenerator *parserGenerator=0, ...);
};

} // namespace Perilib

#endif /* __PERILIB_PROTOCOL_STREAMPROTOCOL_H__ */
