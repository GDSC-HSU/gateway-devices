#! /usr/local/bin/python3
import os
import serial
import time
import random
import sys
import uuid
# its win32, maybe there is win64 too?
is_windows = sys.platform.startswith('win')

PORT = "/dev/tty.usbserial-A50285BI"

if is_windows:
    PORT = "COM5"

arduino = serial.Serial(port=PORT,
                        baudrate=115200, timeout=.1)
counter = 0
key = 0
text = ""


def clear(): return os.system('cls' if os.name == 'nt' else 'clear')


def getUUID():
    totalByte = 22
    return uuid.uuid4().hex[0:totalByte]


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
    formatedText = '''{key}:{counter}'''.format(key=key, counter=float(num)+0.1)
    text = formatedText


def rfid_emulator():
    global text
    key = 4
    num = getUUID()
    formatedText = '''{key}:{counter}'''.format(key=key, counter=num)
    text = formatedText


def radar_emulator():
    global text
    key = 3
    num = random.randrange(0, 1)
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
        proximity_emulator, thermometer_emulator, rfid_emulator,
    ])


def text_to_sensor(text):
    if text == "2":
        return thermometer_emulator
    if text == "3":
        return radar_emulator
    if text == "1":
        return proximity_emulator
    if text == "4":
        return rfid_emulator
    return ""


sensor_table = [["1:", "proximity_emulator"], ["2:", "thermometer_emulator"], [
    "3:", "radar_emulator"], ["4:", "rfid_emulator"]]


while 1:
    print("Type in sensor number to emulate over ble")
    print("-----------")
    for i in sensor_table:
        print('\t'.join(i))
    print("-----------")
    sensorType = input("type in number : ")
    if sensorType != "":
        runner([text_to_sensor(sensorType)])
    else:
        print("Wrong format")
        time.sleep(1.5)
    clear()
    # if text == "":
    #     runner(
    #         [proximity_emulator, thermometer_emulator]
    #     )
