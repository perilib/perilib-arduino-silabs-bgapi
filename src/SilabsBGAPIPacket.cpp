#include "SilabsBGAPIPacket.h"

namespace Perilib
{

int8_t SilabsBGAPIPacket::prepareBufferAfterBuilding()
{
    PERILIB_DEBUG_PRINTLN("SilabsBGAPIPacket::prepareBufferAfterBuilding()");

    // make sure header and payload pointers are correct
    header = (header_t *)&buffer[0];
    payload = (payload_t *)&buffer[4];
    
    // fill BGAPI packet header data
    header->type = (messageType << 7) | (technologyType << 6) | (payloadLength >> 8);
    header->length = (payloadLength & 0xFF);
    header->groupId = definition[0];
    header->methodId = definition[1];
    return Result::OK;
}

} // namespace Perilib
