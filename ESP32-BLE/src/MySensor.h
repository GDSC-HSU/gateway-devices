#include "MyBLE.h"
#include "sensor_pin.h"

/// dependency libary
#include "Adafruit_MLX90614.h"
#include <PN532_SPI.h>
#include <PN532.h>
#include <NfcAdapter.h>
///
#ifndef MYSENSOR_H_
#define MYSENSOR_H_
class MySensor
{
private:

    PN532_SPI spi_interface;
    // (SPI, 5); 

    /* data */
    Adafruit_MLX90614 mlx;
    NfcAdapter nfc;
    //

    MyBLE *pMyBLE;

    void initNFC();
    void initProximity();

    // init Adafruit_MLX90614
    void initThermometer();

    // int 
    void initRadarProximity();
    //

    void isSensorBeginFail(bool beginResult, String sensorName);

public:
    MySensor();
    ~MySensor();

    void init(MyBLE *myBLE);
    bool isMotionApper();
    String readRFID();
    String readProximity();
    String readThermometer();

    void notifyRFID(String value);
    void notifyProximity(String value);
    void notifyThermometer(String value);
};

#endif