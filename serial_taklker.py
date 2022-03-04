#! /usr/local/bin/python3
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


def runner(callbackList):
    # callback List as *_emulator() function
    for callback in callbackList:
        callback()
        arduino.write(bytes(text, 'utf-8'))
        time.sleep(1)


while 1:
    text = input("type in enter")
    if text == "":
        runner([proximity_emulator, thermometer_emulator])
