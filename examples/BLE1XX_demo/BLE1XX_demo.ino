#include <Perilib_Silabs_BGAPI.h>

#define BLE1XX_MODULE_UART_BAUD_RATE 38400
#define BLE1XX_MODULE_USE_PACKET_MODE 1

Perilib::SilabsBGAPIDeviceBLE1XX device(&Serial1);

int8_t onRxPacket(Perilib::StreamPacket *packet)
{
  // create pointer cast to child class
  Perilib::SilabsBGAPIPacket *bgapiPacket = (Perilib::SilabsBGAPIPacket *)packet;
  
  // dump raw packet data in hexadecimal notation
  Serial.print("RXP: [ ");
  uint16_t i;
  for (i = 0; i < bgapiPacket->bufferLength; i++)
  {
    if (bgapiPacket->buffer[i] < 16) Serial.write('0');
    Serial.print(bgapiPacket->buffer[i], HEX);
    Serial.write(' ');
  }
  Serial.println("]");
  
  // display formatted packet based on index
  switch (packet->index)
  {
    case Perilib::SilabsBGAPIProtocolBLE1XX::BLE_RSP_SYSTEM_HELLO:
      Serial.print("ble_rsp_system_hello()\r\n");
      break;
      
    case Perilib::SilabsBGAPIProtocolBLE1XX::BLE_EVT_SYSTEM_BOOT:
      Serial.print("ble_evt_system_boot(");
      Serial.print("major=");               Serial.print(bgapiPacket->payload->ble_evt_system_boot.major);
      Serial.print(", minor=");             Serial.print(bgapiPacket->payload->ble_evt_system_boot.minor);
      Serial.print(", patch=");             Serial.print(bgapiPacket->payload->ble_evt_system_boot.patch);
      Serial.print(", build=");             Serial.print(bgapiPacket->payload->ble_evt_system_boot.build);
      Serial.print(", ll_version=");        Serial.print(bgapiPacket->payload->ble_evt_system_boot.ll_version);
      Serial.print(", protocol_version=");  Serial.print(bgapiPacket->payload->ble_evt_system_boot.protocol_version);
      Serial.print(", hw=");                Serial.print(bgapiPacket->payload->ble_evt_system_boot.hw);
      Serial.print(")\r\n");
      break;
  }
  
  // allow further processing (non-zero to prevent)
  return 0;
}

uint32_t t0;
void setup() {
  // assign callbacks
  device.stream.parserGeneratorPtr->onRxPacket = onRxPacket;
  
  // uncomment the following 
  device.packetMode = BLE1XX_MODULE_USE_PACKET_MODE;
  
  // wait until host opens serial port
  while (!Serial);
  
  // initialize host serial interface for monitoring
  Serial.begin(9600);
  
  // initialize module serial interface for BGAPI communication
  Serial1.begin(BLE1XX_MODULE_UART_BAUD_RATE);
  t0 = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  device.process();
  
  // send system_hello command (ping) once every five seconds
  if (millis() - t0 > 5000) {
    t0 = millis();
    device.sendPacket(Perilib::SilabsBGAPIProtocolBLE1XX::BLE_CMD_SYSTEM_HELLO);
  }
}
