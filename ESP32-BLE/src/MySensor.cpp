#include "MySensor.h"

MySensor::MySensor() {}

void MySensor::isSensorBeginFail(bool beginResult, String sensorName)
{
    if (!beginResult)
    {
        Serial.println("[Dev Error] sensor fail " + sensorName);
    }
}

void MySensor::log(String sensorName , String data)
{
    #ifdef DEBUG_DATA_LOG
        Serial.println("[DEV] SensorData:" + sensorName + "\t" + data);
    #endif
}

void MySensor::init(MyBLE *myBLE, NfcAdapter *nfc, Adafruit_MLX90614 *mlx)
{
    ptr_MyBLE = myBLE;
    initThermometer(mlx);
    initNFC(nfc);
    initRadarProximity();
    initThermometerProximity();
}
void MySensor::initThermometer(Adafruit_MLX90614 *mlx)
{
    bool isWireBegin = Wire.begin(SDA_PIN, SDL_PIN);
    isSensorBeginFail(isWireBegin, "Wire: Adafruit_MLX90614");
    ptr_MLX = mlx;
    bool isMlxBegin = ptr_MLX->begin();
    isSensorBeginFail(isMlxBegin, "Adafruit_MLX90614");
}

void MySensor::initRadarProximity()
{
    // OneButton hanlder
    // pinMode(RADAR_PIN, INPUT);
}

void MySensor::initNFC(NfcAdapter *nfc)
{
    ptr_NFC = nfc;
    ptr_NFC->begin();
}

void MySensor::initThermometerProximity(){
    pinMode(THERMOMETER_PROXIMITY_PIN,INPUT);
}

///----------------------------------
// SENSOR READING

void MySensor::readRFID(bool isNotify)
{
    // void readNFC()
    // {
    if (ptr_NFC->tagPresent())
    {
        NfcTag tag = ptr_NFC->read();
        String tagID = tag.getUidString();
        log("NFC",tagID);
        if (isNotify)
        {
            ptr_MyBLE->setRFID(tagID);        
        }
    }
    // }
}

bool MySensor::isMotionApper(bool isNotify)
{
    // TODO add millis
    int isMotionApper = digitalRead(RADAR_PIN);
    String isMotionApperAsString = String(isMotionApper);
    log("Motion",isMotionApperAsString);
    if (isNotify)
    {
        ptr_MyBLE->setRadar(isMotionApperAsString);
    }
    
    return isMotionApper;
}

void MySensor::readThermometer(bool isNotify)
{
    String temp = String(ptr_MLX->readObjectTempC());
    log("Thermometer",temp);
    if (isNotify)
    {
        ptr_MyBLE->setThermometer(temp);
    }
    
}

bool MySensor::isThermometerProximityEnough(){
    short value = digitalRead(THERMOMETER_PROXIMITY_PIN);
    log("ThermometerProximityEnough",String(value));

    return !value;
}