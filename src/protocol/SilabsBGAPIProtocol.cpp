#include "protocol/SilabsBGAPIProtocol.h"
#include "protocol/SilabsBGAPIPacket.h"

namespace Perilib
{

int8_t SilabsBGAPIProtocol::testPacketComplete(const uint8_t *buffer, uint16_t length, uint8_t newByte, StreamParserGenerator *parserGenerator, bool isTx)
{
    // make sure we have at least the header (3 buffer bytes + 1 new byte)
    if (length > 2)
    {
        // check 11-bit "length" field in 4-byte header
        uint16_t payload_length = ((buffer[0] & 0x03) << 8) + buffer[1];
        if ((length + 1) == (payload_length + 4))
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
