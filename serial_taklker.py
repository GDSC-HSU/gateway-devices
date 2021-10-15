#! /usr/local/bin/python3
import serial
import time
import random

PORT = "/dev/cu.wchusbserial14210"

arduino = serial.Serial(port=PORT,
                        baudrate=115200, timeout=.1)
counter = 0
key = 0
text = ""


def proximity_emulator():
    global text
    key = 97
    num = random.randrange(10, 20)
    formatedText = '''{key}:{counter}'''.format(key=key, counter=num)
    text = formatedText


def thermometer_emulator():
    global text
    key = 65
    num = random.randrange(33, 40)
    formatedText = '''{key}:{counter}'''.format(key=key, counter=num)
    text = formatedText


def runner(callbackList):
    # callback List as *_emulator() function
    for callback in callbackList:
        callback()
        arduino.write(bytes(text, 'utf-8'))
        time.sleep(1)


while 1:
    runner([proximity_emulator, thermometer_emulator])
