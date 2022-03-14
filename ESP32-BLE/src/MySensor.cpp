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
    pinMode(RADAR_PIN, INPUT);
}

void MySensor::initNFC(NfcAdapter *nfc)
{
    ptr_NFC = nfc;
    ptr_NFC->begin();
}

void MySensor::readRFID()
{
    // void readNFC()
    // {
    if (ptr_NFC->tagPresent())
    {
        NfcTag tag = ptr_NFC->read();
        String tagID = tag.getUidString();
        ptr_MyBLE->setRFID(tagID);
    }
    // }
}

bool MySensor::isMotionApper()
{
    // TODO add
    int isMotionApper = digitalRead(RADAR_PIN);
    String isMotionApperAsString = String(ptr_MLX->readObjectTempC());
    ptr_MyBLE->setRadar(isMotionApperAsString);
    if (isMotionApper == HIGH)
    {
        return true;
    }
    return false;
}

void MySensor::readThermometer()
{
    String temp = String(ptr_MLX->readObjectTempC());
    ptr_MyBLE->setThermometer(temp);
}
