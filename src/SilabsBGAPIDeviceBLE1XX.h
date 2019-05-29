#ifndef __PERILIB_SILABSBGAPIDEVICEBLE1XX_H__
#define __PERILIB_SILABSBGAPIDEVICEBLE1XX_H__

#include <Perilib.h>

#include "SilabsBGAPIDevice.h"
#include "SilabsBGAPIProtocolBLE1XX.h"

#define SILABS_BGAPI_BLE1XX_MAX_PACKET_SIZE 64

namespace Perilib
{

class SilabsBGAPIDeviceBLE1XX : public SilabsBGAPIDevice
{
public:
    SilabsBGAPIDeviceBLE1XX(::Stream *arduinoUart)
            : SilabsBGAPIDevice(
                arduinoUart,
                &protocol,
                &lastRxPacket,
                &lastTxPacket,
                rxBuffer, sizeof(rxBuffer),
                txBuffer, sizeof(txBuffer))
       {
           lastRxPacket.technologyType = 0;
           lastTxPacket.technologyType = 0;
       }
    
protected:
    uint8_t rxBuffer[SILABS_BGAPI_BLE1XX_MAX_PACKET_SIZE];
    uint8_t txBuffer[SILABS_BGAPI_BLE1XX_MAX_PACKET_SIZE];
    SilabsBGAPIPacket lastRxPacket;
    SilabsBGAPIPacket lastTxPacket;
    SilabsBGAPIProtocolBLE1XX protocol;
};

} // namespace Perilib

#endif /* __PERILIB_SILABSBGAPIDEVICEBLE1XX_H__ */
