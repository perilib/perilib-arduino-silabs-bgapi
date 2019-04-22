#ifndef __PERILIB_SILABSBGAPIDEVICE_H__
#define __PERILIB_SILABSBGAPIDEVICE_H__

#include <Perilib.h>

#include "SilabsBGAPIProtocol.h"

namespace Perilib
{

class SilabsBGAPIDevice : public StreamDevice
{
public:
    SilabsBGAPIDevice(::Stream *arduinoUart)
            : StreamDevice(&stream),
              parserGenerator(&protocol, rxBuffer, sizeof(rxBuffer)),
              stream(arduinoUart, &parserGenerator, this) { }
    
protected:
    uint8_t rxBuffer[256];
    SilabsBGAPIProtocol protocol;
    StreamParserGenerator parserGenerator;
    UartStream stream;
};

} // namespace Perilib

#endif /* __PERILIB_SILABSBGAPIDEVICE_H__ */
