#ifndef __PERILIB_SILABSBGAPIDEVICEBGM1XX_H__
#define __PERILIB_SILABSBGAPIDEVICEBGM1XX_H__

#include <Perilib.h>

#include "SilabsBGAPIDevice.h"
#include "SilabsBGAPIProtocolBGM1XX.h"

#define SILABS_BGAPI_BGM1XX_MAX_PACKET_SIZE 64

namespace Perilib
{

class SilabsBGAPIDeviceBGM1XX : public SilabsBGAPIDevice
{
public:
    SilabsBGAPIDeviceBGM1XX(::Stream *arduinoUart)
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
    uint8_t rxBuffer[SILABS_BGAPI_BGM1XX_MAX_PACKET_SIZE];
    uint8_t txBuffer[SILABS_BGAPI_BGM1XX_MAX_PACKET_SIZE];
    SilabsBGAPIPacket lastRxPacket;
    SilabsBGAPIPacket lastTxPacket;
    SilabsBGAPIProtocolBGM1XX protocol;
};

} // namespace Perilib

#endif /* __PERILIB_SILABSBGAPIDEVICEBGM1XX_H__ */
