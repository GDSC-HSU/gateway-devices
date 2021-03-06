# gateway-devices
Git submodules contain supported device, board-schematic, mock emulator codebase

##### ```SOLUTION IN ACTION```
We submit our solution in GDSC Solution challenge 2022 base on 17 Sustainable Development Goals of the United Nations more info could be found [here](https://developers.google.com/community/gdsc-solution-challenge) 

Youtube : https://www.youtube.com/watch?v=W5LBuIvWCd8

<a href="http://www.youtube.com/watch?feature=player_embedded&v=W5LBuIvWCd8" target="_blank"><img width=200 src="http://img.youtube.com/vi/W5LBuIvWCd8/0.jpg" 
alt="Gateway - GDSC Solution Challenge 2022"/></a>
#### Installation
1. Platform IO as our IDE of chose for IoT development
[Platform IO - VScode Install](https://platformio.org/install/ide?install=vscode)
1. Follow this guidance (GUI click-click) to add ESP32 build-tool for PlatformIO [here](https://www.youtube.com/watch?v=5edPOlQQKmo)
1. Wait a bit for ESP32 build-tool to be install in PlatformIO (1.2 GB)
1. [ESP32-BLE/ - Folder](./ESP32-BLE/) contain Platform IO project
1. Change PlatformIO USB PORT base on linux/macos , window [file-path](https://github.com/GDSC-HSU/gateway-devices/blob/1f371f100a37d73364ffd409288a2f706fa2dcd2/ESP32-BLE/platformio.ini#L15)
1. Platform IO Build with ESP32 board of your choice **`if you don't have required sensor to run the project`** [follow here to enable emulator suite](#dont-have-board-sensor-"problem-solved") for mockup BLE data over serial

```bash
# minimal step for techie 👨🏻‍💻
1. install Platform IO
2. cd ESP32-BLE/
3. install esp32 build-tool for Platform IO (follow GUI click-click)
4. change usb-port (linux/macos [/dev/ttyUSB], window [COM])
5. Build
```

#### Hardware Part
```Part could be order (cheaply) - here are direct link for visual aspect```

##### ```BLE Board```
1. [ESP32 TTGO T8 V1.7](https://vi.aliexpress.com/item/33043952133.html)
##### ``` Sensor part```
1. [Radar motion Sensor : RCWL-0516](https://www.amazon.com/RCWL-0516-Microwave-Induction-Envistia-Mall/dp/B07QMZF1BV)
1. [RFID/NFC : PN532](https://electropeak.com/pn532-nfc-rfid-reader-writer).
1. [Contact-less Infrared Sensor : MLX90614](https://www.adafruit.com/product/1748)
1. [Cheap proximity sensor : UNKNOWN](https://www.engineersgarage.com/proximity-sensors-optical-ultrasonic-inductive-magnetic-capacitive/) support MLX90614 reading in close range

##### ```3D printed model```

```

- 3D-MODEL/
        - box-pn532.stl"
        - esp32-ttgo-box.STL"
        - motion-dection-box.STL"
        - thermal-and-proximity-box.STL"
 ```

#### Wired diagram
``` work in process```

#### 2. IoT division

Flutter application as an testing suite for IoT BLE is hard-complex to develop "within our develop resource and time"

I suggest using [LightBlue® — Bluetooth Low Energy] [IOS](https://apps.apple.com/us/app/lightblue/id557428110) | [Android](https://play.google.com/store/apps/details?id=com.punchthrough.lightblueexplorer&hl=vi&gl=US) [Window,Mac] also avablie if your machine has BLE

We're using a custom BLE GATT profile which means the UUID will be hard to look at but you guys can base on our documentation [here](https://github.com/GDSC-HSU/gateway-devices/blob/master/ble_uuid_conf.yml) where we define our BLE GATT services, characteristics.

```yml
gatt_profile:
  - BLE_SERVICE_THERMOMETER_UUID: "00000B00-5226-4AE0-8977-656FD3C42DA2"
```

When you get familiar with LightBlue, you will be able to know that every time the BLE board notify LightBlue will get it. But the format is kind of a mess so you have to **decode **it I suggest using a tool on the website http://www.unit-conversion.info/texttools/ascii/ to decode and see the value has been transfer over BLE protocol

```yml
BLE GATT:
 BLE_SERVICE_THERMOMETER_UUID: "00000B00-5226-4AE0-8977-656FD3C42DA2"
data:
 051 051 (ascii) => String: => 33 (ascii decode to text)
meaning: Data from THERMOMETER is 33 
```
---

##### Don't have board sensor "problem solved"
> What I would do when i don't have sensor to connect to BLE Board

You will use **BLE_SENSOR_EMULATOR** in short it allows your machine (PC) talk to BLE Board (ESP32) over serial and send data over BLE GATT.
**BLE_SENSOR_EMULATOR** are [located here](https://github.com/GDSC-HSU/gateway-devices/blob/master/serial_taklker.py) is a Python script with serial comunication

**```step to use```** 

1. Config your **```machine PORT```** in the Python script [here](https://github.com/GDSC-HSU/gateway-devices/blob/f8e9ac8967a8b4b7791e6821dc9990c71e83f9cd/serial_taklker.py#L12)
1. **`Config DEBUG MODE`** in C++ project [located here](./ESP32-BLE/src/device_config.h)
###### Example of BLE SERIAL EMULATOR config

```c
#ifndef DEVICE_CONFIG_H
#define DEVICE_CONFIG_H
/// BLE SERIAL EMULATOR
/// uncomment as enable BLE SERIAL EMULATOR MODE
#define DEBUG

/// SENSOR DATA LOG
#define DEBUG_DATA_LOG
#endif
```
1. base on while loop it will call BLE Board to send each package, you could re-configure to your liking

=> if you still on LightBLue you will see the data been notify

```mermaid
sequenceDiagram
    participant IoT
    participant Mobile
    rect rgb(100, 159, 100)
    IoT->>Mobile:devlopemnt_enviorment
    alt is_ble
        Note over IoT,Mobile:real hardware mobile
    else
        Note over IoT,Mobile:mobile emulator for UI
    end
    end
```
