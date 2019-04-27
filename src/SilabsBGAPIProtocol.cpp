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
    // ensure packet and buffer pointers are valid
    if (!packet || !buffer) return -1;
    
    // assign packet buffer (direct pointer, no copy)
    packet->buffer = buffer;
    
    // assign header and payload pointers
    ((SilabsBGAPIPacket *)packet)->header = (SilabsBGAPIPacket::header_t *)&packet->buffer[0];
    ((SilabsBGAPIPacket *)packet)->payload = (SilabsBGAPIPacket::payload_t *)&packet->buffer[4];
    
    // identify packet
    uint16_t i;
    const uint8_t *search;
    if ((buffer[0] >> 7) == 0)
    {
        // messageType == 0, command (TX) or response (RX)
        search = bleProtocolCommandTable;
        for (i = 0; i < BLE_IDX_CMD_MAX; i++)
        {
            // check for match
            if (search[0] == buffer[2] && search[1] == buffer[3])
            {
                // group/method match, so assign index and stop searching
                ((SilabsBGAPIPacket *)packet)->index = i;
                ((SilabsBGAPIPacket *)packet)->definition = search;
                break;
            }
            
            // jump to next command definition
            search += search[2] + 3;
        }
        
        // if we didn't couldn't identify the packet, stop here
        if (i == BLE_IDX_CMD_MAX) return -2;
    }
    else
    {
        // messageType == 1, event (RX)
        search = bleProtocolEventTable;
        for (i = 0; i < BLE_IDX_EVT_MAX; i++)
        {
            // check for match
            if (search[0] == buffer[2] && search[1] == buffer[3])
            {
                // group/method match, so assign index and stop searching
                ((SilabsBGAPIPacket *)packet)->index = i;
                ((SilabsBGAPIPacket *)packet)->definition = search;
                break;
            }
            
            // jump to next event definition
            search += search[2] + 3;
        }

        // if we didn't couldn't identify the packet, stop here
        if (i == BLE_IDX_EVT_MAX) return -2;
    }
    
    Serial.print("PACKET: [ ");
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

const uint8_t SilabsBGAPIProtocol::bleProtocolCommandTable[] =
{
};

const uint8_t SilabsBGAPIProtocol::bleProtocolEventTable[] =
{
    /* system_boot (ID=0/0) */
        /* group_id */  0x00,
        /* method_id */ 0x00,
        /* arg_count */ 0x07,
        /* evta[0] */   StreamProtocol::UINT16, /* uint16 major */
        /* evta[1] */   StreamProtocol::UINT16, /* uint16 minor */
        /* evta[0] */   StreamProtocol::UINT16, /* uint16 patch */
        /* evta[2] */   StreamProtocol::UINT16, /* uint16 build */
        /* evta[3] */   StreamProtocol::UINT16, /* uint8 ll_version */
        /* evta[4] */   StreamProtocol::UINT8,  /* uint8 protocol_version */
        /* evta[5] */   StreamProtocol::UINT8,  /* uint8 hw */
};

} // namespace Perilib
