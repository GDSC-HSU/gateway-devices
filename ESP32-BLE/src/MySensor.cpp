#include "MySensor.h"

MySensor::MySensor() {}

void MySensor::isSensorBeginFail(bool beginResult, String sensorName)
{
    if (!beginResult)
    {
        Serial.println("[Dev Error] sensor fail " + sensorName);
    }
}

void MySensor::log(String text)
{
    Serial.println(text);
}

void MySensor::init(MyBLE *myBLE, NfcAdapter *nfc, Adafruit_MLX90614 *mlx)
{
    ptr_MyBLE = myBLE;
    initThermometer(mlx);
    initNFC(nfc);
    initRadarProximity();
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

    if (isNotify)
    {
        String isMotionApperAsString = String(isMotionApper);
        ptr_MyBLE->setRadar(isMotionApperAsString);
    }
    
    return isMotionApper;
}

void MySensor::readThermometer(bool isNotify)
{
    String temp = String(ptr_MLX->readObjectTempC());
    if (isNotify)
    {
        ptr_MyBLE->setThermometer(temp);
    }
    
}
