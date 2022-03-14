#include "MySensor.h"


void MySensor::isSensorBeginFail(bool beginResult, String sensorName){
    if (!beginResult)
    {
        Serial.println("[Dev Error] sensor fail " + sensorName);
    }
}

void MySensor::init(MyBLE *ble){
    pMyBLE = ble;
    initThermometer();
    initNFC();
    initRadarProximity();
}
void MySensor::initThermometer(){
    bool isWireBegin = Wire.begin(SDA_PIN,SDL_PIN);
    isSensorBeginFail(isWireBegin,"Wire: Adafruit_MLX90614");
    mlx = Adafruit_MLX90614();
    bool isMlxBegin = mlx.begin();
    isSensorBeginFail(isMlxBegin,"Adafruit_MLX90614");
}

void MySensor::initRadarProximity(){
    pinMode(RADAR_PIN,INPUT);
}

void MySensor::initNFC(){
    // spi_interface = PN532_SPI(SPI,SPI_CS);
    // nfc = NfcAdapter(spi_interface);
    // nfc.begin();
    // NO LOG
}
