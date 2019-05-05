#ifndef __PERILIB_SILABSBGAPIPROTOCOL_H__
#define __PERILIB_SILABSBGAPIPROTOCOL_H__

#include <Perilib.h>

namespace Perilib
{
    
class SilabsBGAPIProtocol : public StreamProtocol
{
public:
    // {{ START perilib_protocol_cpp_index_enum_list }}
    enum ble_idx_t {
        BLE_IDX_CMD_SYSTEM_RESET,
        BLE_IDX_CMD_SYSTEM_HELLO,
        BLE_IDX_CMD_SYSTEM_WHITELIST_APPEND,
        BLE_IDX_CMD_MAX,
        
        BLE_IDX_RSP_SYSTEM_RESET,
        BLE_IDX_RSP_SYSTEM_HELLO,
        BLE_IDX_RSP_SYSTEM_WHITELIST_APPEND,
        BLE_IDX_RSP_MAX,
        
        BLE_IDX_EVT_SYSTEM_BOOT,
        BLE_IDX_EVT_MAX
    };
    // {{ END perilib_protocol_cpp_index_enum_list }}
    
    // {{ START perilib_protocol_cpp_packet_struct_set }}
    // {{ END perilib_protocol_cpp_packet_struct_set }}

    SilabsBGAPIProtocol();
    virtual int8_t testPacketComplete(const uint8_t *buffer, uint16_t length, StreamParserGenerator *parserGenerator=0, bool isTx=false);
    virtual int8_t getPacketFromBuffer(StreamPacket *packet, const uint8_t *buffer, uint16_t length, StreamParserGenerator *parserGenerator=0, bool isTx=false);
    virtual int8_t getPacketFromNameAndArgs(StreamPacket *packet, const char *packetName, StreamParserGenerator *parserGenerator=0, ...);
    virtual int8_t getPacketDefinition(uint16_t index, const uint8_t **packetDef);
    virtual uint8_t getArgumentCount(uint16_t index, const uint8_t *packetDef);
    virtual const uint8_t *getFirstArgument(uint16_t index, const uint8_t *packetDef);

private:
    static const uint8_t bleProtocolCommandTable[];
    static const uint8_t bleProtocolEventTable[];

};

} // namespace Perilib

#endif /* __PERILIB_STREAMPROTOCOL_H__ */
