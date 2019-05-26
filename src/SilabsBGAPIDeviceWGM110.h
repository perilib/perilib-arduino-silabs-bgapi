#ifndef __PERILIB_SILABSBGAPIDEVICEWGM110_H__
#define __PERILIB_SILABSBGAPIDEVICEWGM110_H__

#include <Perilib.h>

#include "SilabsBGAPIDevice.h"
#include "SilabsBGAPIProtocolWGM110.h"

#define SILABS_BGAPI_WGM121_MAX_PACKET_SIZE 272

namespace Perilib
{

class SilabsBGAPIDeviceWGM110 : public SilabsBGAPIDevice
{
public:
    SilabsBGAPIDeviceWGM110(::Stream *arduinoUart)
            : SilabsBGAPIDevice(
                arduinoUart,
                &protocol,
                &lastRxPacket,
                &lastTxPacket,
                rxBuffer, sizeof(rxBuffer),
                txBuffer, sizeof(txBuffer))
       {
           lastRxPacket->technologyType = 0;
           lastTxPacket->technologyType = 0;
       }
    
protected:
    uint8_t rxBuffer[2];
    uint8_t txBuffer[64];
    SilabsBGAPIPacket lastRxPacket;
    SilabsBGAPIPacket lastTxPacket;
    SilabsBGAPIProtocolWGM110 protocol;
};

} // namespace Perilib

#endif /* __PERILIB_SILABSBGAPIDEVICEWGM110_H__ */
