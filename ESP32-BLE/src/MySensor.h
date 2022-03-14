#include "MyBLE.h"
#include "sensor_pin.h"

/// dependency libary
#ifndef Adafruit_MLX90614_H
#define Adafruit_MLX90614_H
#include "Adafruit_MLX90614.h"
#endif
///

#include "MyBLE.h"

#include "NfcAdapter.h"
///
#ifndef MYSENSOR_H_
#define MYSENSOR_H_
class MySensor
{
private:
    // (SPI, 5);

    MyBLE *ptr_MyBLE;

    /* data */
    Adafruit_MLX90614 *ptr_MLX;
    NfcAdapter *ptr_NFC;
    //
    void initProximity();

    // init Adafruit_MLX90614
    void initThermometer(Adafruit_MLX90614 *mlx);

    // int
    void initRadarProximity();
    //
    void initNFC(NfcAdapter *nfc);
    void log(String text);

    //

    void isSensorBeginFail(bool beginResult, String sensorName);

public:
    MySensor();

    void init(MyBLE *myBLE, NfcAdapter *nfc, Adafruit_MLX90614 *mlx);
    bool isMotionApper();
    void readRFID();
    void readProximity();
    void readThermometer();

    void notifyRFID(String value);
    void notifyProximity(String value);
    void notifyThermometer(String value);
};

#endif