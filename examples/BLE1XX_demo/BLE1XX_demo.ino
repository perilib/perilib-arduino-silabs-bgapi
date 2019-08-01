#include <Perilib_Silabs_BGAPI.h>

#define BLE1XX_UART_BAUD_RATE           38400
#define BLE1XX_USE_PACKET_MODE          1
#define BLE1XX_WAKE_PIN                 2
#define BLE1XX_WAKE_PIN_ASSERTED_STATE  HIGH
#define BLE1XX_RESET_PIN                3

#ifdef SERIAL_PORT_PERILIB
    #define BLESerial SERIAL_PORT_PERILIB
#else
    // assume no hardware ports available, switch to software (original Arduino Uno)
    #include <SoftwareSerial.h>
    SoftwareSerial BLESerial(10, 11); // RX, TX
#endif

Perilib::SilabsBGAPIDeviceBLE1XX device(&BLESerial);

// track intervals between commands
uint32_t t0;

void setup() {
  // assign callbacks
  device.stream.parserGeneratorPtr->onRxPacket = onRxPacket;
  
  // uncomment the following to use BGAPI in "packet" mode
  // (<length> prefix byte for outgoing transmissions)
  device.packetMode = BLE1XX_USE_PACKET_MODE;

  // configure GPIO control
  device.wakePin = BLE1XX_WAKE_PIN;
  device.wakePinAssertedState = BLE1XX_WAKE_PIN_ASSERTED_STATE;
  device.resetPin = BLE1XX_RESET_PIN;
  
  // wait until host opens serial port
  while (!Serial);
  
  // initialize host serial interface for monitoring
  Serial.begin(9600);
  
  // initialize module serial interface for BGAPI communication
  BLESerial.begin(BLE1XX_UART_BAUD_RATE);
  
  // perform hardware reset on device
  device.reset();

  // initialize reference time
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

int8_t onRxPacket(Perilib::StreamPacket *packet)
{
  // create pointer cast to child class
  Perilib::SilabsBGAPIPacketBLE1XX *bgapiPacket = (Perilib::SilabsBGAPIPacketBLE1XX *)packet;
  
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
      
    default:
      Serial.print("Unhandled packet: index=");
      Serial.print(packet->index);
      Serial.print(", type=");
      Serial.print(bgapiPacket->messageType);
      Serial.print(", group=");
      Serial.print(bgapiPacket->header->groupId);
      Serial.print(", method=");
      Serial.println(bgapiPacket->header->methodId);
  }
  
  // allow further processing (non-zero to prevent)
  return 0;
}
