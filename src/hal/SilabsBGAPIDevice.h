#ifndef __PERILIB_HAL_SILABSBGAPIDEVICE_H__
#define __PERILIB_HAL_SILABSBGAPIDEVICE_H__

#include <Perilib.h>

#include "protocol/SilabsBGAPIProtocol.h"

namespace Perilib
{

class SilabsBGAPIDevice : public StreamDevice
{
public:
    SilabsBGAPIDevice(::Stream *arduinoUart)
            : StreamDevice(&stream),
              parserGenerator(&protocol),
              stream(arduinoUart, &parserGenerator, this) { }
    
protected:
    SilabsBGAPIProtocol protocol;
    StreamParserGenerator parserGenerator;
    UartStream stream;
};

} // namespace Perilib

#endif /* __PERILIB_HAL_SILABSBGAPIDEVICE_H__ */
