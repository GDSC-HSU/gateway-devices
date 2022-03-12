#include "NimBLEDevice.h"
#include "BLE_DESIGN.g.h"
bool deviceConnected = false;

// Hidden wrapper class for setting GATT Server (Services, Characteristics)
// TODO Make ESP32 running 2 core with xTask
// Task are reading sensor and calling BLE wrapper
// https://www.youtube.com/watch?v=El7_ZUn6NeU
// using RTOS (Roud Robin Queue base one [execution quota] to comsume task)
// https://github.com/chegewara/esp32-OTA-over-BLE/blob/master/BLE_server/main/main_ble.cpp

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
            deviceConnected = true;
        }

        void onDisconnect(NimBLEServer *pServer, ble_gap_conn_desc *desc)
        {
            // CMT ARE COPIED FROM SNIPPET !

            // Peer disconnected, add them to the whitelist
            // This allows us to use the whitelist to filter connection attempts
            // which will minimize reconnection time.
            NimBLEDevice::whiteListAdd(NimBLEAddress(desc->peer_ota_addr));
            deviceConnected = false;
        }
        void onMTUChange(uint16_t MTU, ble_gap_conn_desc *desc)
        {
            Serial.printf("MTU updated: %u for connection ID: %u\n", MTU, desc->conn_handle);
        };
    };
};
// TODO Setup for other services
MyBLE::MyBLE() {}

MyBLE::~MyBLE()
{
}

void MyBLE::init(NimBLEServer *pBLE_SERVER)
{
    gpServer = pBLE_SERVER;
    gpServer->setCallbacks(new MyBLEServerCallbacks());
    // gpServer->start()

    // Bringing ours BLE Services up and it corrsponding charecteristic
    proximityBLE();
    thermometerBLE();
    radarBLE();
    rfidBLE();

    /// Advertisting GATT
    const char *manufacturer = "GDSC-HSU:v0.1.2";
    NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
    // pAdvertising->addServiceUUID(BLE_SERVICE_PROXIMITY_UUID);
    pAdvertising->addServiceUUID(BLE_SERVICE_PROXIMITY_UUID);
    pAdvertising->addServiceUUID(BLE_SERVICE_THERMOMETER_UUID);
    pAdvertising->addServiceUUID(BLE_SERVICE_RADAR_UUID);
    pAdvertising->addServiceUUID(BLE_SERVICE_RFID_UUID);
    pAdvertising->setManufacturerData(manufacturer);
    pAdvertising->start();
    ////
}

void MyBLE::proximityBLE()
{
    pProximityServices = gpServer->createService(BLE_SERVICE_PROXIMITY_UUID);
    pProximityServices->createCharacteristic(BLE_CHARACTERISTIC_PROXIMITY_DISTANCE, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    pProximityServices->start();
}

void MyBLE::thermometerBLE()
{
    pThermometerServices = gpServer->createService(BLE_SERVICE_THERMOMETER_UUID);
    pThermometerServices->createCharacteristic(BLE_CHARACTERISTIC_THERMOMETER_READ, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    pThermometerServices->start();
}

void MyBLE::radarBLE()
{
    pRadarServices = gpServer->createService(BLE_SERVICE_RADAR_UUID);
    pRadarServices->createCharacteristic(BLE_CHARACTERISTIC_RADAR_UUID, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    pRadarServices->start();
}

void MyBLE::otaBLE()
{
    pOTAServices = gpServer->createService(BLE_SERVICE_OTA_UUID);
    // BLE_CHARACTERISTIC_OTA_CONTROL to acknowledgment current version checking
    pOTAServices->createCharacteristic(BLE_CHARACTERISTIC_OTA_CONTROL, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);

    pOTAServices->createCharacteristic(BLE_CHARACTERISTIC_OTA_WRITE_NO_RSP, NIMBLE_PROPERTY::WRITE_NR);
}

void MyBLE::rfidBLE()
{
    pRFIDServices = gpServer->createService(BLE_SERVICE_RFID_UUID);
    pRFIDServices->createCharacteristic(BLE_CHARACTERISTIC_RFID_READ, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    pRFIDServices->start();
}

/// ------------------ SET BLE DATA AND NOTIFY TO MOBILE APP
void MyBLE::setProximity(String number, bool isNotify)
{
    NimBLECharacteristic *pCharacteristic = pProximityServices->getCharacteristic(BLE_CHARACTERISTIC_PROXIMITY_DISTANCE);
    pCharacteristic->setValue(std::string(number.c_str()));
    if (isNotify)
    {
        pCharacteristic->notify();
    }
}
void MyBLE::setThermometer(String number, bool isNotify)
{
    NimBLECharacteristic *pCharacteristic = pThermometerServices->getCharacteristic(BLE_CHARACTERISTIC_THERMOMETER_READ);
    pCharacteristic->setValue(std::string(number.c_str()));
    if (isNotify)
    {
        pCharacteristic->notify();
    }
}

void MyBLE::setRadar(String number, bool isNotify)
{
    NimBLECharacteristic *pCharacteristic = pRadarServices->getCharacteristic(BLE_CHARACTERISTIC_RADAR_UUID);
    pCharacteristic->setValue(std::string(number.c_str()));
    if (isNotify)
    {
        pCharacteristic->notify();
    }
}

void MyBLE::setRFID(String number, bool isNotify)
{
    NimBLECharacteristic *pCharacteristic = pRFIDServices->getCharacteristic(BLE_CHARACTERISTIC_RFID_READ);
    pCharacteristic->setValue(std::string(number.c_str()));
    if (isNotify)
    {
        pCharacteristic->notify();
    }
}