#include <Arduino.h>
#include <NimBLEDevice.h>
#include <BLE_DESIGN.g.h>
#include <MyBLE.h>

// gpServer is use to controlling BLE GATT with sensor
static NimBLEServer *gpServer;

// Hidden wrapper for gatt server setup & control central pairing
static MyBLE myBLE;
void setup()
{
  Serial.begin(115200);
  Serial.println("Starting BLE server");
  NimBLEDevice::init("esp32 gateway");
  NimBLEDevice::setPower(ESP_PWR_LVL_P9);
  gpServer = NimBLEDevice::createServer();
  myBLE.init(gpServer);
}

// control sensor data state and calling gatt services and characteristics
void loop()
{
}