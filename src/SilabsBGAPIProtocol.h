#ifndef __PERILIB_SILABSBGAPIPROTOCOL_H__
#define __PERILIB_SILABSBGAPIPROTOCOL_H__

#include <Perilib.h>

namespace Perilib
{
    
class SilabsBGAPIProtocol : public StreamProtocol
{
public:
    enum ble_idx_cmd_t {
        BLE_IDX_CMD_MAX
    };
    
    enum ble_idx_evt_t {
        BLE_IDX_EVT_SYSTEM_BOOT,
        BLE_IDX_EVT_MAX
    };
    
    SilabsBGAPIProtocol();
    virtual int8_t testPacketComplete(const uint8_t *buffer, uint16_t length, StreamParserGenerator *parserGenerator=0, bool isTx=false);
    virtual int8_t getPacketFromBuffer(StreamPacket *packet, const uint8_t *buffer, uint16_t length, StreamParserGenerator *parserGenerator=0, bool isTx=false);
    virtual int8_t getPacketFromNameAndArgs(StreamPacket *packet, const char *packetName, StreamParserGenerator *parserGenerator=0, ...);

private:
    static const uint8_t bleProtocolCommandTable[];
    static const uint8_t bleProtocolEventTable[];

};

} // namespace Perilib

#endif /* __PERILIB_STREAMPROTOCOL_H__ */
