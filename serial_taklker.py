#! /usr/local/bin/python3
import os
import serial
import time
import random
import sys
# its win32, maybe there is win64 too?
is_windows = sys.platform.startswith('win')


PORT = "/dev/cu.wchusbserial14210"

if is_windows:
    PORT = "COM3"

arduino = serial.Serial(port=PORT,
                        baudrate=115200, timeout=.1)
counter = 0
key = 0
text = ""


def clear(): return os.system('cls' if os.name == 'nt' else 'clear')


def proximity_emulator():
    global text
    key = 1
    num = random.randrange(10, 20)
    formatedText = '''{key}:{counter}'''.format(key=key, counter=num)
    text = formatedText


def thermometer_emulator():
    global text
    key = 2
    num = random.randrange(33, 40)
    formatedText = '''{key}:{counter}'''.format(key=key, counter=num)
    text = formatedText


def presence_emulator():
    global text
    key = 3
    num = "1"
    formatedText = '''{key}:{counter}'''.format(key=key, counter=num)
    text = formatedText


def rfid_emulator():
    global text
    key = 4
    num = "z23az"
    formatedText = '''{key}:{counter}'''.format(key=key, counter=num)
    text = formatedText


def runner(callbackList):
    # callback List as *_emulator() function
    for callback in callbackList:
        callback()
        arduino.write(bytes(text, 'utf-8'))
        time.sleep(0.5)


def suite_normal():
    runner([
        presence_emulator, proximity_emulator, thermometer_emulator, rfid_emulator,
    ])


def text_to_sensor(text):
    if text == "1":
        return presence_emulator
    if text == "2":
        return thermometer_emulator
    if text == "3":
        return rfid_emulator
    if text == "4":
        return proximity_emulator
    return


sensor_table = [["1:", "presence_emulator"], ["2:", "thermometer_emulator"], [
    "3:", "rfid_emulator"], ["4:", "proximity_emulator"]]

while 1:
    print("Type in sensor number to emulate over ble")
    print("-----------")
    for i in sensor_table:
        print('\t'.join(i))
    print("-----------")
    sensorType = input("type in number : ")
    runner(text_to_sensor(sensorType))
    clear()
    # if text == "":
    #     runner(
    #         [proximity_emulator, thermometer_emulator]
    #     )
