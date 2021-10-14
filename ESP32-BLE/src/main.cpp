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

/* TODO mock create fake sensor data :> (currently in order & shipping :>)
  - [x] proximity
  - [ ] thermometer
*/
// TODO web-client for to controlling sensor over serial (python,nodejs maybe)
// using keyboard input suck, web forward port client UI just click click :)) we could writing ours testcases
// key/data (97:15)-> 97 for calling proximity - 15cm in range :>

// control sensor data state and calling gatt services and characteristics
String serialInput;
int key;
int value;

void parsingCommandFromSerial()
{
  serialInput = Serial.readStringUntil('\n');
  int index = serialInput.indexOf(":");
  key = atoi(serialInput.substring(0, index).c_str());
  value = atoi(serialInput.substring(index + 1, serialInput.length()).c_str());
}

void loop()
{
  while (Serial.available())
  {
    parsingCommandFromSerial();
    Serial.print(key);
    Serial.print(":");
    Serial.print(value);
    if (key == 97)
    {
      myBLE.setProximity(value);
    }
    Serial.flush();
  }
}
