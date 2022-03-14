#include <Arduino.h>
#include <NimBLEDevice.h>
#include "NimBLEDevice.h"
#include "BLE_DESIGN.g.h"

// Hidden wrapper class for setting GATT Server (Services, Characteristics)
// TODO Make ESP32 running 2 core with xTask
// Task are reading sensor and calling BLE wrapper
// https://www.youtube.com/watch?v=El7_ZUn6NeU
// using RTOS (Roud Robin Queue base one [execution quota] to comsume task)
// https://github.com/chegewara/esp32-OTA-over-BLE/blob/master/BLE_server/main/main_ble.cpp


#ifndef MYBLE_H_
#define MYBLE_H_
class MyBLE
{
private:
    NimBLEServer *gpServer;
    NimBLEService *pProximityServices;
    NimBLEService *pThermometerServices;
    NimBLEService *pRadarServices;
    NimBLEService *pRFIDServices;

    NimBLEService *pOTAServices;

    // Abstaction for bring-up services & charecteristic
    void proximityBLE();
    void thermometerBLE();
    void otaBLE();
    void configModeBLE();
    void radarBLE();
    void rfidBLE();
    ///

    /* data */
public:
    MyBLE();
    ~MyBLE();
    void init(NimBLEServer *pBLE_SERVER);
    void setProximity(String number, bool isNotify = true);
    void setThermometer(String number, bool isNotify = true);
    void setRadar(String number, bool isNotify = true);
    void setRFID(String number, bool isNotify = true);
    // TODO :> OTA
    void enableOTA();

    class MyBLEServerCallbacks : public NimBLEServerCallbacks
    {
        // TODO enable connected (1) -> gat disable advertise GATT profile packages for CPU, power mather
        void onConnect(NimBLEServer *pServer)
        {
            // deviceConnected = true;
        }

        void onDisconnect(NimBLEServer *pServer, ble_gap_conn_desc *desc)
        {
            // CMT ARE COPIED FROM SNIPPET !

            // Peer disconnected, add them to the whitelist
            // This allows us to use the whitelist to filter connection attempts
            // which will minimize reconnection time.
            NimBLEDevice::whiteListAdd(NimBLEAddress(desc->peer_ota_addr));
            // deviceConnected = false;
        }
        void onMTUChange(uint16_t MTU, ble_gap_conn_desc *desc)
        {
            Serial.printf("MTU updated: %u for connection ID: %u\n", MTU, desc->conn_handle);
        };
    };
};
#endif