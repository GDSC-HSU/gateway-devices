#include <Arduino.h>
#include <NimBLEDevice.h>
#include <BLE_DESIGN.g.h>
#include <MyBLE.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();


// #define DEBUG

// gpServer is use to controlling BLE GATT with sensor
static NimBLEServer *gpServer;

// Hidden wrapper for gatt server setup & control central pairing
static MyBLE myBLE;

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting BLE server");
  NimBLEDevice::init(DEVICE_NAME);
  NimBLEDevice::setPower(ESP_PWR_LVL_P9);
  gpServer = NimBLEDevice::createServer();
  myBLE.init(gpServer);
  
  while (!Serial);

  Serial.println("Adafruit MLX90614 test");
  if(!Wire.begin(21,22)){
        Serial.println("Error Wire.begin(21,2)");

  }
  if (!mlx.begin()) {
    Serial.println("Error connecting to MLX sensor. Check wiring.");
    while (1);
  };
}

#ifdef DEBUG
/* TODO mock create fake sensor data :> (currently in order & shipping :>)
  - [x] proximity
  - [x] thermometer
*/
// TODO web-client for to controlling sensor over serial (python,nodejs maybe)
// using keyboard input suck, web forward port client UI just click click :)) we could writing ours testcases
// key/data (97:15)-> 97 for calling proximity - 15cm in range :>

// control sensor data state and calling gatt services and characteristics
String serialInput;
int key;
String value;

void parsingCommandFromSerial()
{
  serialInput = Serial.readStringUntil('\n');
  int index = serialInput.indexOf(":");
  key = atoi(serialInput.substring(0, index).c_str());
  value = serialInput.substring(index + 1, serialInput.length());
}
#endif

void loop()
{
#ifdef DEBUG
  while (Serial.available())
  {
    parsingCommandFromSerial();
    Serial.println(key);
    switch (key)
    {
    case 1:
      myBLE.setProximity(value);
      break;
    case 2:
      myBLE.setThermometer(value);
      break;
    case 3:
      myBLE.setRadar(value);
      break;
    case 4:
      myBLE.setRFID(value);
      break;
    default:
      break;
    }
    Serial.println(value);
    Serial.flush();
  }
#endif
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC());
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF());
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");

  Serial.println();
  delay(500);
  //
}
