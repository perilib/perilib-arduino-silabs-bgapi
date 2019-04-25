#include "SilabsBGAPIProtocol.h"
#include "SilabsBGAPIPacket.h"

namespace Perilib
{

SilabsBGAPIProtocol::SilabsBGAPIProtocol()
{
    incomingPacketTimeoutMs = 500;
    responsePacketTimeoutMs = 1200;
}

int8_t SilabsBGAPIProtocol::testPacketComplete(const uint8_t *buffer, uint16_t length, StreamParserGenerator *parserGenerator, bool isTx)
{
    // make sure we have at least the header (4 bytes)
    if (length > 3)
    {
        // check 11-bit "length" field in 4-byte header
        uint16_t payload_length = ((buffer[0] & 0x03) << 8) + buffer[1];
        if (length == (payload_length + 4))
        {
            // existing buffer plus new byte is expected length
            return ParseStatus::COMPLETE;
        }
    }

    // not finished if we made it here
    return ParseStatus::IN_PROGRESS;
}

int8_t SilabsBGAPIProtocol::getPacketFromBuffer(StreamPacket *packet, const uint8_t *buffer, uint16_t length, StreamParserGenerator *parserGenerator, bool isTx)
{
    // ensure packet is not null
    if (!packet) return -1;
    
    // pointer packet buffer at RX buffer
    packet->buffer = buffer;
    
    // fill in header data
    ((SilabsBGAPIPacket *)packet)->header = (SilabsBGAPIPacket::header_t *)packet->buffer;
    
    Serial.print("PACKET: [ ");
    uint16_t i;
    for (i = 0; i < length; i++)
    {
        if (buffer[i] < 16) Serial.write('0');
        Serial.print(buffer[i], HEX);
        Serial.write(' ');
    }
    Serial.println("]");
    return 0;
}

int8_t SilabsBGAPIProtocol::getPacketFromNameAndArgs(StreamPacket *packet, const char *packetName, StreamParserGenerator *parserGenerator, ...)
{
    return 0;
}

} // namespace Perilib
