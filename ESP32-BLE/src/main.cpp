#include <Arduino.h>
#include <device_config.h>
#include <NimBLEDevice.h>
#include <BLE_DESIGN.g.h>

///
#ifndef Adafruit_MLX90614_H
#define Adafruit_MLX90614_H
#include <Adafruit_MLX90614.h>
#endif
//

#include <PN532_SPI.h>
#include <PN532.h>
#include <NfcAdapter.h>
//
#include <MyBLE.h>

//
#include <MySensor.h>

///
#include <Bounce2.h>


// gpServer is use to controlling BLE GATT with sensor
static NimBLEServer *gpServer;

// Hidden wrapper for gatt server setup & control central pairing
static MyBLE myBLE;
static MySensor mySensor;

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
PN532_SPI interface(SPI, 5);
NfcAdapter nfc = NfcAdapter(interface);
Bounce radarBounce = Bounce(); // Instantiate a Bounce object

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting BLE server");
  NimBLEDevice::init(DEVICE_NAME);
  NimBLEDevice::setPower(ESP_PWR_LVL_P9);
  gpServer = NimBLEDevice::createServer();
  myBLE.init(gpServer);
  delay(1000);
  #ifndef DEBUG
  mySensor.init(&myBLE, &nfc, &mlx);
  delay(1000);
  radarBounce.attach(RADAR_PIN, INPUT);
  #endif
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

  // BLE SENSOR DATA SERIAL COMMUNICATION EMULATOR
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

#ifndef DEBUG
/* TODO common interface for logging in 
 - [] MySensor 
 - [] MyBLe
*/
if (myBLE.isMobileConnected())
{
 
  radarBounce.update();
 if (radarBounce.rose())
 {
    mySensor.isMotionApper();
 }
 if(radarBounce.fell()){
    mySensor.isMotionApper();
 }
 if(radarBounce.read()== HIGH){
    mySensor.readRFID();
    if (mySensor.isThermometerProximityEnough())
    {
      mySensor.readThermometer();
    }
 }
}

// Serial.println(radarBounce.read());
#endif
}
