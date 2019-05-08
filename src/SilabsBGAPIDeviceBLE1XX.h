#ifndef __PERILIB_SILABSBGAPIDEVICEBLE1XX_H__
#define __PERILIB_SILABSBGAPIDEVICEBLE1XX_H__

#include <Perilib.h>

#include "SilabsBGAPIDevice.h"
#include "SilabsBGAPIProtocolBLE1XX.h"

namespace Perilib
{

class SilabsBGAPIDeviceBLE1XX : public SilabsBGAPIDevice
{
public:
    SilabsBGAPIDeviceBLE1XX(::Stream *arduinoUart)
            : SilabsBGAPIDevice(arduinoUart, &protocol, rxBuffer, sizeof(rxBuffer), txBuffer, sizeof(txBuffer)) { }
    
protected:
    uint8_t rxBuffer[64];
    uint8_t txBuffer[64];
    SilabsBGAPIProtocolBLE1XX protocol;
};

} // namespace Perilib

#endif /* __PERILIB_SILABSBGAPIDEVICEBLE1XX_H__ */
