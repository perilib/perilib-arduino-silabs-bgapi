#include <Perilib_Silabs_BGAPI.h>

Perilib::SilabsBGAPIDeviceBLE1XX device(&Serial1);

int8_t onRxPacket(Perilib::StreamPacket *packet)
{
  // create pointer cast to child class
  Perilib::SilabsBGAPIPacket *bgapiPacket = (Perilib::SilabsBGAPIPacket *)packet;
  
  // dump raw packet data
  Serial.print("RXP: [");
  Serial.write(bgapiPacket->buffer, bgapiPacket->bufferLength);
  Serial.println("]");
  
  switch (packet->index)
  {
    case Perilib::SilabsBGAPIProtocolBLE1XX::BLE_EVT_SYSTEM_BOOT:
      Serial.println(bgapiPacket->payload->ble_evt_system_boot.major);
      Serial.println(bgapiPacket->payload->ble_evt_system_boot.minor);
      Serial.println(bgapiPacket->payload->ble_evt_system_boot.patch);
      Serial.println(bgapiPacket->payload->ble_evt_system_boot.build);
      Serial.println(bgapiPacket->payload->ble_evt_system_boot.ll_version);
      Serial.println(bgapiPacket->payload->ble_evt_system_boot.protocol_version);
      Serial.println(bgapiPacket->payload->ble_evt_system_boot.hw);
      break;
  }
  
  // allow further processing (non-zero to prevent)
  return 0;
}

uint32_t t0;
void setup() {
  // assign callbacks
  device.stream.parserGenerator->onRxPacket = onRxPacket;
  
  // wait until host opens serial port
  while (!Serial);
  
  // initialize host serial interface for monitoring
  Serial.begin(9600);
  
  // initialize module serial interface for BGAPI communication
  Serial1.begin(38400);
  t0 = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  device.process();
  if (millis() - t0 > 5000) {
    t0 = millis();

    Serial.println(device.stream.parserGenerator->sendPacket(Perilib::SilabsBGAPIProtocolBLE1XX::BLE_EVT_SYSTEM_BOOT, 1, 4, 0, 138, 1, 1, 8));
    //Serial.println(parserGenerator->sendPacket(Perilib::SilabsBGAPIProtocolBLE1XX::BLE_RSP_SYSTEM_WHITELIST_APPEND, 0x0204));
  }
}
