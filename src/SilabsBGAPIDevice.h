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
              parserGenerator(&protocol),
              stream(arduinoUart, &parserGenerator, this) { }
    
protected:
    SilabsBGAPIProtocol protocol;
    StreamParserGenerator parserGenerator;
    UartStream stream;
};

} // namespace Perilib

#endif /* __PERILIB_SILABSBGAPIDEVICE_H__ */
