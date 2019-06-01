#ifndef __PERILIB_SILABSBGAPIDEVICEWF121_H__
#define __PERILIB_SILABSBGAPIDEVICEWF121_H__

#include <Perilib.h>

#include "SilabsBGAPIDevice.h"
#include "SilabsBGAPIProtocolWF121.h"

#define SILABS_BGAPI_WF121_MAX_RX_PACKET_SIZE 272
#define SILABS_BGAPI_WF121_MAX_TX_PACKET_SIZE 272

namespace Perilib
{

class SilabsBGAPIDeviceWF121 : public SilabsBGAPIDevice
{
public:
    SilabsBGAPIDeviceWF121(::Stream *arduinoUart)
            : SilabsBGAPIDevice(
                arduinoUart,
                &protocol,
                &lastRxPacket,
                &lastTxPacket,
                rxBuffer, sizeof(rxBuffer),
                txBuffer, sizeof(txBuffer))
       {
           lastRxPacket.technologyType = 1;
           lastTxPacket.technologyType = 1;
       }
    
protected:
    uint8_t rxBuffer[SILABS_BGAPI_WF121_MAX_RX_PACKET_SIZE];
    uint8_t txBuffer[SILABS_BGAPI_WF121_MAX_TX_PACKET_SIZE];
    SilabsBGAPIPacket lastRxPacket;
    SilabsBGAPIPacket lastTxPacket;
    SilabsBGAPIProtocolWF121 protocol;
};

} // namespace Perilib

#endif /* __PERILIB_SILABSBGAPIDEVICEWF121_H__ */
