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
    SilabsBGAPIProtocol *bgapiProtocol = (SilabsBGAPIProtocol *)parserGenerator->protocol;
    Serial.print("INDEX="); Serial.println(index);
    Serial.print("MAXRSP="); Serial.println(bgapiProtocol->maxResponseIndex);
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
