#include "MyBLE.h"
#include "sensor_pin.h"
#include "device_config.h"

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
    void initThermometerProximity();

    // init Adafruit_MLX90614
    void initThermometer(Adafruit_MLX90614 *mlx);

    // int
    void initRadarProximity();
    //
    void initNFC(NfcAdapter *nfc);
    void log(String sensorName , String data);

    //

    void isSensorBeginFail(bool beginResult, String sensorName);

public:
    MySensor();

    void init(MyBLE *myBLE, NfcAdapter *nfc, Adafruit_MLX90614 *mlx);
    bool isMotionApper(bool isNotify = true);
    void readRFID(bool isNotify = true);
    void readProximity(bool isNotify = true);
    void readThermometer(bool isNotify = true);

    bool isThermometerProximityEnough();


    // void notifyRFID(String value);
    // void notifyProximity(String value);
    // void notifyThermometer(String value);
    // void notifyRadar(bool value);
};

#endif