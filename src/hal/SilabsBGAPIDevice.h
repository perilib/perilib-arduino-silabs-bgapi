#ifndef __PERILIB_HAL_SILABSBGAPIDEVICE_H__
#define __PERILIB_HAL_SILABSBGAPIDEVICE_H__

#include <Perilib.h>

#include "protocol/SilabsBGAPIProtocol.h"

namespace Perilib
{

class SilabsBGAPIDevice : public SerialDevice
{
public:
    SilabsBGAPIDevice(::Stream *arduinoStream)
            : pargen(&protocol),
              stream(arduinoStream, &pargen) { }
    
protected:
    SilabsBGAPIProtocol protocol;
    StreamParserGenerator pargen;
    SerialStream stream;
};

} // namespace Perilib

#endif /* __PERILIB_HAL_SILABSBGAPIDEVICE_H__ */
