#include "NimBLEDevice.h"
#include "BLE_DESIGN.g.h"
bool deviceConnected = false;

// Hidden wrapper class for setting GATT Server (Services, Characteristics)
class MyBLE
{
private:
    NimBLEServer *gpServer;
    NimBLEService *pProximityServices;
    void proximityBLE();
    void thermometerSerices();
    void configModeBLE();

    /* data */
public:
    MyBLE();
    ~MyBLE();
    void init(NimBLEServer *pBLE_SERVER);

    class MyBLEServerCallbacks : public NimBLEServerCallbacks
    {
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

MyBLE::MyBLE() {}

MyBLE::~MyBLE()
{
}
void MyBLE::init(NimBLEServer *pBLE_SERVER)
{
    gpServer = pBLE_SERVER;
    gpServer->setCallbacks(new MyBLEServerCallbacks());
    // gpServer->start()
    /// Advertisting GATT
    proximityBLE();
    NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(BLE_SERVICE_PROXIMITY_UUID);
    pAdvertising->start();
    ////
}

void MyBLE::proximityBLE()
{
    pProximityServices = gpServer->createService(BLE_SERVICE_PROXIMITY_UUID);
    NimBLECharacteristic *pProximityCharacteristic = pProximityServices->createCharacteristic(BLE_CHARACTERISTIC_PROXIMITY_DISTANCE, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::NOTIFY);
    pProximityServices->start();
}

void MyBLE::configModeBLE()
{
}
