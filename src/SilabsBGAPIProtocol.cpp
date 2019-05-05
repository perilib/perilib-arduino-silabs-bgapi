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
            search += search[2] + search[3] + 4;
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
    // TODO: THIS
    return 0;
}

int8_t SilabsBGAPIProtocol::getPacketDefinition(uint16_t index, const uint8_t **packetDef)
{
    // ensure destination pointer is valid
    if (!packetDef) return -1;
    
    // determine correct look-up table and search range, assume commands
    const uint8_t *search = SilabsBGAPIProtocol::bleProtocolCommandTable;
    uint16_t max = BLE_IDX_CMD_MAX;
    uint8_t tableId = 0;
    if (index > BLE_IDX_CMD_MAX)
    {
        // switch to event table
        search = SilabsBGAPIProtocol::bleProtocolEventTable;
        index -= (BLE_IDX_CMD_MAX + 1);
        max = BLE_IDX_EVT_MAX - (BLE_IDX_CMD_MAX + 1);
        tableId = 1;
    }
    
    // abort if requested packet is out of range
    if (index >= max) return -2;
    
    // jump through [index] definitions to obtain requested entry
    uint16_t i;
    for (i = 0; i < index; i++)
    {
        if (tableId == 0)
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
    return 0;
}

uint8_t SilabsBGAPIProtocol::getArgumentCount(uint16_t index, const uint8_t *packetDef)
{
    if (packetDef) return packetDef[2];
    else return 0;
}

const uint8_t *SilabsBGAPIProtocol::getFirstArgument(uint16_t index, const uint8_t *packetDef)
{
    if (!packetDef) return 0;
    if (index < BLE_IDX_CMD_MAX) return &packetDef[4];
    return &packetDef[3];
}

const uint8_t SilabsBGAPIProtocol::bleProtocolCommandTable[] =
{
    /* system_reset (ID=0/0) */
        /* group_id */      0x00,
        /* method_id */     0x00,
        /* outarg_count */  0x01,
        /* inarg_count */   0x80,
        /* cmda[0] */       UINT8,
        
    /* system_hello (ID=0/1) */
        /* group_id */      0x00,
        /* method_id */     0x01,
        /* outarg_count */  0x00,
        /* inarg_count */   0x00,
};

const uint8_t SilabsBGAPIProtocol::bleProtocolEventTable[] =
{
    /* system_boot (ID=0/0) */
        /* group_id */      0x00,
        /* method_id */     0x00,
        /* inarg_count */   0x07,
        /* evta[0] */       UINT16, /* uint16 major */
        /* evta[1] */       UINT16, /* uint16 minor */
        /* evta[2] */       UINT16, /* uint16 patch */
        /* evta[3] */       UINT16, /* uint16 build */
        /* evta[4] */       UINT16, /* uint16 ll_version */
        /* evta[5] */       UINT8,  /* uint8 protocol_version */
        /* evta[6] */       UINT8,  /* uint8 hw */
};

} // namespace Perilib
