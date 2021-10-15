#! /usr/local/bin/python3
import yaml

pathTOHeaderFile = "./ESP32-BLE/src/BLE_DESIGN.g.h"

pathToDartFile = "../lib/config/constants/ble_desgin_constants.g.dart"

deviceId = "esp32-gateway"


def read_config():
    with open("./ble_uuid_conf.yml") as f:
        data = yaml.load(f, Loader=yaml.FullLoader)
        # yaml.load()
        # return list of key and value pair
        return(data["gatt_profile"])


def cHeaderFileLimbo(listOfData):
    output = ""
    for i in listOfData:
        for key, value in i.items():
            text = '''#ifndef {key}\n#define {key} "{value}"\n#endif
            '''.format(key=key, value=value)
            output += text + "\n"
    return output


def dartCode(listOfData):
    deviceName = '''const String DEVICE_NAME = "{deviceId}";'''.format(
        deviceId=deviceId)
    # import required library
    output = "//Genrate in git submodule (ble_devices) -> ble_uuid+generator.py" + \
        "\nimport 'package:flutter_reactive_ble/flutter_reactive_ble.dart';\n"
    servicesAsList = ""
    geneteuuid = ""
    for i in listOfData:
        for key, value in i.items():
            text = '''Uuid {key} = Uuid.parse("{value}");
            '''.format(key=key, value=value)
            geneteuuid += text + "\n"
            if "SERVICE" in key:
                servicesAsList += '''{key},'''.format(key=key)

    servicesUUIDasListExport = '''List<Uuid> deviceServices = [{services}];'''.format(
        services=servicesAsList)
    return output+geneteuuid+"\n"+servicesUUIDasListExport+"\n"+deviceName


def generate(fileGenrateCallback, fileLocation):
    text = "//THIS IS GENERATED IN ble_uuid_conf.yml\n"
    text += fileGenrateCallback(read_config())
    f = open(fileLocation, 'w')
    f.write(text)
    f.close()


def run():
    generate(dartCode, pathToDartFile)
    generate(cHeaderFileLimbo, pathTOHeaderFile)


run()
