#! /usr/local/bin/python3
import serial
import time
import random

arduino = serial.Serial(port='/dev/cu.wchusbserial14210',
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


while 1:
    proximity_emulator()
    arduino.write(bytes(text, 'utf-8'))
    time.sleep(1)
