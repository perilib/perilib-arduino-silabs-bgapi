#include "SilabsBGAPIPacket.h"

namespace Perilib
{

int8_t SilabsBGAPIPacket::prepareBufferAfterBuilding()
{
    PERILIB_DEBUG_PRINTLN("SilabsBGAPIPacket::prepareBufferAfterBuilding()");

    // fill BGAPI packet header data
    header->type = 0xAA;
    header->length = 0xBB;
    header->groupId = definition[0];
    header->methodId = definition[1];
    return Result::OK;
}

} // namespace Perilib
