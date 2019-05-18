#ifndef __PERILIB_SILABSBGAPIDEVICE_H__
#define __PERILIB_SILABSBGAPIDEVICE_H__

#include <Perilib.h>

#include "SilabsBGAPIProtocol.h"
#include "SilabsBGAPIPacket.h"

namespace Perilib
{

class SilabsBGAPIDevice : public StreamDevice
{
public:
    SilabsBGAPIDevice(
        ::Stream *arduinoUart,
        SilabsBGAPIProtocol *protocol,
        SilabsBGAPIPacket *lastRxPacket,
        SilabsBGAPIPacket *lastTxPacket,
        uint8_t *rxBuffer,
        uint16_t rxBufferSize,
        uint8_t *txBuffer,
        uint16_t txBufferSize)
            : StreamDevice(&stream),
              parserGenerator(protocol, lastRxPacket, lastTxPacket, rxBuffer, rxBufferSize, txBuffer, txBufferSize),
              stream(arduinoUart, &parserGenerator, this) { }
    
protected:
    StreamParserGenerator parserGenerator;
    UartStream stream;
};

} // namespace Perilib

#endif /* __PERILIB_SILABSBGAPIDEVICE_H__ */
