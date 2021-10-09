#! /usr/local/bin/python3
import yaml

pathTOHeaderFile = "./ESP32-BLE/src/BLE_DESIGN.g.h"


def read_config():
    with open("./ble_uuid_conf.yml") as f:
        data = yaml.load(f, Loader=yaml.FullLoader)
        # yaml.load()
        # return list of key and value pair
        return(data["gatt_profile"])


def cHeaderFileLimbo(data):
    output = ""
    for key, value in data.items():
        text = '''#ifndef {key}\n#define {key} "{value}"\n#endif
        '''.format(key=key, value=value)
        output += text + "\n"
    return output


def dartCode():
    print("Not impl yet")


def generate():
    text = "//THIS IS GENERATED IN ble_uuid_conf.yml\n"
    for i in read_config():
        text += cHeaderFileLimbo(i)
    f = open(pathTOHeaderFile, 'w')
    f.write(text)


generate()
