#ifndef __PERILIB_SILABSBGAPIDEVICEBT121_H__
#define __PERILIB_SILABSBGAPIDEVICEBT121_H__

#include <Perilib.h>

#include "SilabsBGAPIDevice.h"
#include "SilabsBGAPIProtocolBT121.h"

#define SILABS_BGAPI_BT121_MAX_PACKET_SIZE 272

namespace Perilib
{

class SilabsBGAPIDeviceBT121 : public SilabsBGAPIDevice
{
public:
    SilabsBGAPIDeviceBT121(::Stream *arduinoUart)
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
    uint8_t rxBuffer[SILABS_BGAPI_BT121_MAX_PACKET_SIZE];
    uint8_t txBuffer[SILABS_BGAPI_BT121_MAX_PACKET_SIZE];
    SilabsBGAPIPacket lastRxPacket;
    SilabsBGAPIPacket lastTxPacket;
    SilabsBGAPIProtocolBT121 protocol;
};

} // namespace Perilib

#endif /* __PERILIB_SILABSBGAPIDEVICEBT121_H__ */
